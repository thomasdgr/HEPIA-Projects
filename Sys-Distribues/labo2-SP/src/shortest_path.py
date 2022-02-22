import distributed_alg as globals_Var

def determineSet(table_routage, t):
    set = []
    for ele in table_routage:
        if(ele['distance'] == t):
            set.append(ele['id'])
    return set

def handle_Conn(data, t, table_routage, setT):
    
    print(data)
    id_recv = data.get("id")
    noeud_kDis_recv = data.get("noeud_kDis")        
    t_preced = data.get("t")
    
    for noeud_kDis in noeud_kDis_recv:
        globals_Var.lock.acquire()
        try:
            if table_routage[noeud_kDis-1]['distance'] > t and t_preced + 1 == t:
                table_routage[noeud_kDis-1]['distance'] = t
                table_routage[noeud_kDis-1]['next'] = id_recv
                setT.append(noeud_kDis)
        finally:
            globals_Var.lock.release()
    
    globals_Var.barrier.wait()  
    #print(table_routage)  
    
        
    

    

    
    