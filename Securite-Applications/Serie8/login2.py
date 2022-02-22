import base64
import hashlib
import html
import json
import os
import re
import urllib.parse
import requests
from pynput import keyboard
from pynput.keyboard import Key, Controller

#https://www.stefaanlippens.net/oauth-code-flow-pkce.html

try :

    id = input("Welcome, enter Login ID: ")
    passwd = input("Please, enter Password: ")

    print()
    print({'acr': '1',
'aud': 'pkce-test',
 'auth_time': 156321239,
 'azp': 'pkce-test',
 'email_verified': False,
 'exp': 1561273640,
 'iat': 1561273640,
 'iss': 'http://localhost:9090/auth/realms/master',
 'jti': '96adf1ab9-6c56-4c7f-a17d-5cf234d2497',
 'nbf': 0,
 'preferred_username': 'Dweck',
 'session_state': 'af0afey2c9-0341-25af-b1ad-c6df2345c175',
 'sub': '103456bf-a1d2-4c83f-b39e-465dka4e138',
 'typ': 'ID'})
    print()

    provider = "http://localhost:9090/auth/realms/master"
    client_id = "pkce-test"
    username = id
    password = passwd
    redirect_uri = "http://localhost/foobar"


    code_verifier = base64.urlsafe_b64encode(os.urandom(40)).decode('utf-8')
    code_verifier = re.sub('[^a-zA-Z0-9]+', '', code_verifier)
    #print(code_verifier, len(code_verifier))

    code_challenge = hashlib.sha256(code_verifier.encode('utf-8')).digest()
    code_challenge = base64.urlsafe_b64encode(code_challenge).decode('utf-8')
    code_challenge = code_challenge.replace('=', '')
    #print(code_challenge, len(code_challenge))



    state = "fooobarbaz"
    resp = requests.get(
        url=provider + "/protocol/openid-connect/auth",
        params={
            "response_type": "code",
            "client_id": client_id,
            "scope": "openid",
            "redirect_uri": redirect_uri,
            "state": state,
            "code_challenge": code_challenge,
            "code_challenge_method": "S256",
        },
        allow_redirects=False
    )
    #print(resp.status_code)


    cookie = resp.headers['Set-Cookie']
    cookie = '; '.join(c.split(';')[0] for c in cookie.split(', '))
    #print(cookie)



    page = resp.text
    form_action = html.unescape(re.search('<form\s+.*?\s+action="(.*?)"', page, re.DOTALL).group(1))
    #print(form_action)



    resp = requests.post(
        url=form_action, 
        data={
            "username": username,
            "password": password,
        }, 
        headers={"Cookie": cookie},
        allow_redirects=False
    )
    #print(resp.status_code)


    #MARCHE PAS POUR L'INSTANT
    redirect = resp.headers['Location']
    #print(redirect)
    assert redirect.startswith(redirect_uri)



    query = urllib.parse.urlparse(redirect).query
    redirect_params = urllib.parse.parse_qs(query)
    #print(redirect_params)



    auth_code = redirect_params['code'][0]
    #print(auth_code)



    resp = requests.post(
        url=provider + "/protocol/openid-connect/token",
        data={
            "grant_type": "authorization_code",
            "client_id": client_id,
            "redirect_uri": redirect_uri,
            "code": auth_code,
            "code_verifier": code_verifier,
        },
        allow_redirects=False
    )
    #print(resp.status_code)

    result = resp.json()
    #print(result)

    def _b64_decode(data):
        data += '=' * (4 - len(data) % 4)
        return base64.b64decode(data).decode('utf-8')

    def jwt_payload_decode(jwt):
        _, payload, _ = jwt.split('.')
        return json.loads(_b64_decode(payload))

    jwt_payload_decode(result['access_token'])

    jwt_payload_decode(result['access_token'])

    print("Welcom back !")

except:
    print("Sorry, wrong credentials...")