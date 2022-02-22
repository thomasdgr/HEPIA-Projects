#!/usr/bin/env python3

"""Module responsible for communicating with RFID Reader
"""

import data
import random
from typing import List, Set, Dict, Tuple, Optional
import serial
import io
import time
import string
import math
import time
import array
import time
import yaml
import sys
import RFID

__author__ = ["Quentin Rod", "Thomas Dagier", "Xavier Perret"]
__email__ = [
    "quentin.rod@etu.hesge.ch",
    "thomas.dagier@etu.hesge.ch",
    "xavier.perret@etu.hesge.ch",
]
__date__ = "23/11/2021"

serial_uart = None
timeout_read_one_mess_ms : int = 0
timeout_wait_cmd_answ_ms : int = 0

class RFIDAnswer:
    def __init__(self, cmd_name : str, cmd_code : str, cmd_val : str):
        self.cmd_name = cmd_name
        self.cmd_code = cmd_code
        self.cmd_val = cmd_val

    @staticmethod
    #Convert raw data in RFIDAnswer
    def convert_string_answer(answer_string):
        list_of_val = answer_string.replace(chr(2),'').replace(chr(3),'').split()
        return RFIDAnswer(list_of_val[0], list_of_val[1], list_of_val[2])

    def __str__(self):
        return "cmd: " + self.cmd_name + ", code: " + self.cmd_code + ", val: " + self.cmd_val

def get_time_in_ms() -> int:
    return int(round(time.time() * 1000))

#Send a command over UART.
#cmd is only the command. Parameters are not included. Example "SSTS K0"
def RFID_reader_send_cmd(cmd : str) -> None:
    #print("cmd sent: " + cmd)
    cmd = " " + cmd
    cmd_bytes_string = ""

    cmd_bytes_array = cmd.encode()
    for byte in cmd_bytes_array:
        cmd_bytes_string = cmd_bytes_string + str(hex(byte)).replace("0x","") #Convert and remove "0x"

    cmd_bytes_string=  "02" + cmd_bytes_string + "03"
    serial_uart.write(bytearray.fromhex(cmd_bytes_string))

#Wait an answer of a command for a certain period of time and return the answer.
#cmd_name is only the command. Parameters are not included. Ex: "ERZO"
#return isTimeout, answer
def RFID_wait_answer_of_cmd(cmd_name : str) -> RFIDAnswer:
    answer_uart_string = ''
    begin_time_ms = get_time_in_ms()

    while cmd_name not in answer_uart_string:
        #Get current time for timeout
        current_time_ms = get_time_in_ms()
        if current_time_ms - begin_time_ms >= timeout_wait_cmd_answ_ms:
            return True, RFIDAnswer("", "", 0)
        answer_uart_bytes = serial_uart.read(timeout_read_one_mess_ms)
        answer_uart_string = answer_uart_bytes.decode("utf-8")
        #print("wait", answer_uart_string)

    return False, RFIDAnswer.convert_string_answer(answer_uart_string)

#Init the RFID reader.
#conf_timeout_read_one_mess_ms: Number of ms to read on UART
#conf_timeout_wait_cmd_answ_ms: Number of ms to consider the module doesn't respond
#conf_serial_port_name: Serial Port to discuss with RFID reader
#is_EU: is for Europe use
#do_low_power: low power output mode or not. Max 15 if true, else 33dBm
#do_low_range:  Do low range or not
#<!>This function has to be called before calling others !!
def RFID_reader_init(conf_timeout_read_one_mess_ms : int, conf_timeout_wait_cmd_answ_ms : int, conf_serial_port_name : string, is_EU : bool, do_low_power, do_low_range) -> None:
    global serial_uart
    global timeout_wait_cmd_answ_ms
    global timeout_read_one_mess_ms

    timeout_read_one_mess_ms = conf_timeout_read_one_mess_ms
    timeout_wait_cmd_answ_ms = conf_timeout_wait_cmd_answ_ms
    try:
        serial_uart = serial.Serial(conf_serial_port_name, 115200, timeout= 1)
    except:
        print("Impossible to connect to " + conf_serial_port_name)
        sys.exit(1)

    region = "EU" if is_EU else "US"
    power = 15 if do_low_power else 33
    range = "LP" if do_low_range else "HP"

    RFID_reader_send_cmd("ERZO K0 " + region) #Use reader in EU frequencies
    is_timeout, answer = RFID_wait_answer_of_cmd("ERZO")
    if is_timeout or answer.cmd_val != region :
        if not is_timeout:
            print("ERROR: Bad answer command")
        else:
            print("ERROR: Timeout occured")
        sys.exit(1)

    RFID_reader_send_cmd("EROP K0 " + str(power)) #Biggest emission power
    is_timeout, answer = RFID_wait_answer_of_cmd("EROP")
    if is_timeout or answer.cmd_val != str(power) :
        if not is_timeout:
            print("ERROR: Bad answer command")
        else:
            print("ERROR: Timeout occured")
        sys.exit(1)

    RFID_reader_send_cmd("EROM K0 " + str(range)) #High range
    is_timeout, answer = RFID_wait_answer_of_cmd("EROM")
    if is_timeout or answer.cmd_val != str(range) :
        if not is_timeout:
            print("ERROR: Bad answer command")
        else:
            print("ERROR: Timeout occured")
        sys.exit(1)

    print("INIT OK")

#Asks to the RFID Reader current tags. Return them
#Returns empty list if timeout or no tag detected
def RFID_read_tags() -> List[RFID.Tag]:
    RFID_reader_send_cmd("SSTS K0") #Ask inventary
    is_timeout, answer = RFID_wait_answer_of_cmd("SSTS")
    answer = answer.cmd_val
    #print("answer", answer)

    elements_to_remove = ["[dBm]", " ", "{", "}", chr(2), chr(3)]
    for el in elements_to_remove:
        answer = answer.replace(el, '')

    if answer == "": #No tag detected
        return []

    list_tags = []
    list_string_tags = answer.split(',') #Puts all tags info in a list
    for string_tag in list_string_tags:
        string_tag = string_tag.split(':') #Separates ID from RSSI
        tag = RFID.Tag(string_tag[0], int(string_tag[1]))
        list_tags.append(tag)

    #RFID.Tag.print_list(list_tags)
    return list_tags
