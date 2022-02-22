from typing import List
from pydantic import BaseModel
from fastapi import FastAPI, Query
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from typing import Optional, Dict
from back import *

app = FastAPI()

# Solve issues due to CORS-Origin
origins = [
    "http://localhost",
    "http://localhost:8080",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=[""],
    allow_headers=[""],
)

#Get a list of all person stored in the DB
@app.get("/person/")
async def get_all_persons():
    return JSONResponse(content=get_all_pers())

#Return, if possible, a person from his tag_id
@app.get("/person/get_from_tag_id/{tag_id}")
async def get_person_from_tag_id(tag_id: str):
    return JSONResponse(content=get_person_of(tag_id))

#Return, if possible, a person from his id
@app.get("/tag/get_from_user_id/{pers_id}")
async def get_from_user_id(pers_id: int):
    return JSONResponse(content=get_tag_id_of(pers_id))

#Actualise all presences in the DB
@app.post("/presence/actualize/")
async def post_new_data(new_infos: DataFromRaspberry):
    handle_new_infos_from_raspberry(new_infos)

#Return, if possible, a presence from the id of the person
@app.get("/presence/get_from_user_id/{pers_id}")
async def get_presence_with_user_id(pers_id: int):
    return JSONResponse(content=get_presence_from_user_id(pers_id))

#Return, if possible, a presence from the tag_id of the person
@app.get("/presence/get_from_tag_id/{tag_id}")
async def get_presence_with_tag_id(tag_id: str):
    return JSONResponse(content=get_presence_from_tag_id(tag_id))

#Get a list of all stands
@app.get("/stand/")
async def get_all_stands():
    return JSONResponse(content=get_all_stand())
