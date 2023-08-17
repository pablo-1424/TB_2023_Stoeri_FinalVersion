import mysql.connector
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.dates as mdates


# Function to connect to mySQL database
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


# Connection to the database
db = connectMySQL()
cursor = db.cursor()

# Data recuperation from mySQl :
# First line : All datas
# Second line : 6 last datas

cursor.execute("SELECT * FROM myDataForWater")
#cursor.execute("SELECT * FROM myDataForWater ORDER BY idmyDataForWater DESC LIMIT 6")

data = cursor.fetchall()

# Close connection
cursor.close()
db.close()

# If there are some datas
if data:
    # Select what I want from the datas
    x_data = [item[1] for item in data]  # ChatGPT helped
    y_data = [item[2] for item in data]  # ChatGPT helped
    print(x_data)
    print(y_data)

    # invert order
    x_data.reverse()
    y_data.reverse()

    # Create the graph
    plt.stem(x_data, y_data, basefmt="lightblue")

    # Formtating to good date format
    plt.gcf().autofmt_xdate()  # ChatGPT helped
    date_format = mdates.DateFormatter('%d-%m %H:%M')  # ChatGPT helped
    plt.gca().xaxis.set_major_formatter(date_format)  # ChatGPT helped

    # Name the axes and show plot
    plt.title("Litres consommés par cycle")
    plt.xlabel("Temps")
    plt.ylabel("Litres")
    plt.show()
