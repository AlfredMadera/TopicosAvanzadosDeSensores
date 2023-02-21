import serial, time, keyboard
from datetime import datetime
import xlsxwriter

# Abrir archivo
#file = open("GPSdata.txt","a")
#nowTime = datetime.now()

# Creando archivo de excel
workbook = xlsxwriter.Workbook("GPSdata1.xlsx")
worksheet = workbook.add_worksheet()

worksheet.write(1,1,"Latitud")
worksheet.write(1,2,"Longitud")

nowH = datetime.today().hour

worksheet.write(1,4,"Inicio")
worksheet.write(2,4,str(nowH)+":"+str(datetime.today().minute))

fila = 2
columna = 1
cont = 0

# Configuración serial 
arduino = serial.Serial('COM7', 9600)
# Darle tiempo para que se conecte el serial
time.sleep(2)

while True: 
    # Terminar en 2 o 3 hrs aprox
    if((datetime.today().hour - nowH >= 2) or (keyboard.is_pressed('|'))):
        break
    else:
        if (cont%2 == 0):
            data = arduino.readline() 
            dataSTR = data.decode()
            worksheet.write(fila, 1, dataSTR)
        else:
            data = arduino.readline() 
            dataSTR = data.decode()
            worksheet.write(fila, 2, dataSTR)
            fila += 1
        cont += 1

worksheet.write(1,5,"Termino")
worksheet.write(2,5,str(datetime.today().hour)+":"+str(datetime.today().minute))

workbook.close()    
arduino.close()

    #fila += 1
#    file.write(dataSTR)
#    while (data > 0)
#        # Escribir latitud
#        GPSdata.write('A{}', 'dataLAT')
     
