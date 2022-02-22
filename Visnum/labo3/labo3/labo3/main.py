from typing import List
from pydantic import BaseModel
from fastapi import FastAPI, Query
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse

#import pour appeler les fonctions du backend
from backend.back import deviner, stocker, entrainer

app = FastAPI()

# règle partiellement les problèmes de CORS-Origin
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

# type d'objet envoyé depuis le frontend ici puis
# transmis au backend par la suite
class Item(BaseModel):
    data: List[int] # le tableau
    number_ref: int # le nombre représenté par le tableau

@app.post("/deviner/")
async def create_item1(item: Item):
    # il faut convertir le np_array retourné par le backend en json
    return JSONResponse(content=deviner(item.data).tolist())

@app.post("/stocker/")
async def create_item2(item: Item):
    stocker(item.data, item.number_ref)

@app.get("/entrainer/")
async def create_item3():
    entrainer()