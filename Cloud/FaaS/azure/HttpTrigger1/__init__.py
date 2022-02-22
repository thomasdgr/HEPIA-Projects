import logging
import json
import azure.functions as func

def main(req: func.HttpRequest, doc:func.DocumentList) -> func.HttpResponse:
    
    logging.info('Python HTTP trigger function processed a request.')
    entries_json = []
    print("hello")
    for entry in doc:
        entry_json = {
            "id": entry['id'],
            "AlbumTitle": entry['AlbumTitle'],
            "Artist": entry['Artist'],
            "SongTitle": entry['SongTitle'],
            "Awards": entry['Awards'],
        }
        entries_json.append(entry_json)

    return func.HttpResponse(
            json.dumps(entries_json),
            status_code=200,
            mimetype="application/json"            
    )