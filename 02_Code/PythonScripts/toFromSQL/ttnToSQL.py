import paho.mqtt.client as mqtt
import matplotlib.pyplot as plt
import mysql.connector

# 3000 is the value from the lab test bench
literPerHour = 3000
literPerMinute = literPerHour/60
literPerSecond = literPerMinute/60

# Called when connect to ttn with threw MQTT
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("v3/stm32-sdk@ttn/devices/eui-70b3d57ed005fbd3/up")

# Connect to mySQL function
def connectMySQL():
    try:
        db = mysql.connector.connect(
                        host='localhost', #local host ou ip de l'ordi
                        port=3306, # normalemen c'est bon
                        user='root',
                        passwd='Past-1234',
                        database='tb_stoeri',
                        auth_plugin='mysql_native_password',
                        connection_timeout=10)
        return db
    except mysql.connector.Error as e:
        print("ERROR %d: %s" % (e.args[0], e.args[1]))

# If a message arrives on TTN, that function is called
def on_message(client, userdata, msg):
    # Print the topic and the payload to see all the info
    print(msg.topic+" "+str(msg.payload))

    # Take out of the payload only the seconds value
    pos = str(msg.payload).find('bytes')
    realPayload = ''
    for i in range(20) :
        realPayload = realPayload + str(msg.payload)[i+pos+8]

    secondsOnly = ''
    pos = str(realPayload).find(',0,255,0,136')
    for i in range(pos) :
        secondsOnly = secondsOnly + realPayload[i]

    # Separate both bytes from each other
    separate = secondsOnly.split(',')
    print(separate)
    # Put the two bytes together with there right multiple
    secondsData = int(separate[0])*16*16+int(separate[1])
    literData = secondsData * literPerSecond
    pos = str(msg.payload).find('"time":')
    time = ''
    for i in range(20) :
        time = time + str(msg.payload)[i+pos+8]
    print(time)

    #Connect to the database
    db = connectMySQL()
    curs = db.cursor()

    # Insert into the data base
    curs.execute("INSERT INTO `tb_stoeri`.`myDataForWater` (`waterQuantity`) VALUES ('%d');"%(literData))
    db.commit()

# Créer le client
client = mqtt.Client()

# Attribution of callbacks
client.on_connect = on_connect
client.on_message = on_message

# Connect the MQTT client
client.username_pw_set("stm32-sdk@ttn", password="NNSXS.TE7XOKOXJLU23LH7LULQJA3X7PCBBMMFOAG3FXQ.ABVOACQEIKI2WACI47347B4XERHANTPZDV23GX4XFSSKZVQAGJCQ")
client.connect("eu1.cloud.thethings.network", 1883, 60)

# Loop loop forever
client.loop_forever()