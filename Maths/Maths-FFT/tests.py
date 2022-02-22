def miroir(list_ck_sample):
    list_ck_sample_result = list_ck_sample
    freq_conv = 1/((len(list_ck_sample)*2)/44100)
    #end = int((len(list_ck_sample)/2)+6000)
    for i_ck in range(0, len(list_ck_sample)):
        if i_ck >= 0 and i_ck <= (12000/freq_conv):
            #print(str(i_ck) + " -> " + str(6000+(6000-i_ck)))
            list_ck_sample_result[i_ck] = list_ck_sample[int((6000/freq_conv)+((6000/freq_conv)-i_ck))]
            #list_ck_sample[i_ck], list_ck_sample[6000+6000-i_ck] = list_ck_sample[6000+6000-i_ck], list_ck_sample[i_ck]
            #list_ck_sample[6000+i_ck], list_ck_sample[6000-i_ck] = list_ck_sample[6000-i_ck], list_ck_sample[6000+i_ck]
        #else:
            #list_ck_sample_result[i_ck] = 0.0
    return (np.fft.irfft(list_ck_sample)).tolist()

def translation(list_ck_sample):
    M=len(list_ck_sample)
    L = int(0.1*(M))
    list_ck_sample_result= list_ck_sample
    for i_ck in range(0, int(M/2)):
        if((i_ck+L)<int(M/2)):
            list_ck_sample_result[i_ck] = list_ck_sample[i_ck+L]
        else:
            list_ck_sample_result[i_ck]= list_ck_sample[((i_ck+L)%M)]
    return (np.fft.ifft(list_ck_sample_result)).tolist()

def filtre_passe_haut(list_ck_sample):
    M=len(list_ck_sample)
    for i_ck in range(0, len(list_ck_sample)):
        list_ck_sample[i_ck] = list_ck_sample[i_ck] /(0.1 + 0.9*np.abs(i_ck)/int(M/2))
    return (np.fft.ifft(list_ck_sample)).tolist()