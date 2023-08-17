import serial
import mysql.connector

# Not used for this test
literPerHour = 0
# According to the document from Steve Maillard
literPerMinute = 2000
# Conversion
literPerSecond = literPerMinute/60

# Connect to mySQL function
def connectMySQL():
    try:
        db = mysql.connector.connect(
                        host='localhost',
                        port=3306,
                        user='root',
                        passwd='Past-1234',
                        database='tb_stoeri',
                        auth_plugin='mysql_native_password',
                        connection_timeout=10)
        return db
    except mysql.connector.Error as e:
        print("ERROR %d: %s" % (e.args[0], e.args[1]))

# Open Serial port COM8 with baudrate = 9600
# No other parameters needed
ser = serial.Serial('COM8',9600)

#Forever loop
while 1 :
    serVal = ser.readline().decode().strip()        #Read Line from Serial
    print(serVal)
    if "Seconds : " in serVal :                     #Does the line have "Seconds : " in it
        serVal = serVal.replace('Seconds : ', '')
        print(serVal)
        valToSQL = int(serVal) * literPerSecond     # Convert in liters
        db = connectMySQL()                         # Call connect function
        curs = db.cursor()

        # Insert datas in database
        curs.execute("INSERT INTO `tb_stoeri`.`myDataForWater` (`waterQuantity`) VALUES ('%d');" % (valToSQL))
        db.commit()