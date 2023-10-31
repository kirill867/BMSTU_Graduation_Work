# Создание базы данных

mycursor = mydb.cursor()
mycursor.execute("Drop TABLE IF EXISTS object_type")
mycursor.execute("Drop TABLE IF EXISTS specifications_cannonball")
mycursor.execute("Drop TABLE IF EXISTS flight_cannonball")
mycursor.execute("Drop TABLE IF EXISTS specifications_air_balloon")
mycursor.execute("Drop TABLE IF EXISTS flight_air_balloon")
mycursor.execute("Drop TABLE IF EXISTS specifications_bird")
mycursor.execute("Drop TABLE IF EXISTS flight_bird")
mycursor.execute("CREATE TABLE specifications_cannonball (specifications_cannonball_id INT AUTO_INCREMENT PRIMARY KEY, mass FLOAT, radius FLOAT, density FLOAT, id_object INT)")
mycursor.execute("CREATE TABLE flight_cannonball (flight_cannonball_id INT AUTO_INCREMENT PRIMARY KEY, x FLOAT, y FLOAT, Vx FLOAT, Vy FLOAT)")
mycursor.execute("CREATE TABLE specifications_air_balloon (specifications_air_balloon_id INT AUTO_INCREMENT PRIMARY KEY, mass FLOAT, radius FLOAT, density FLOAT, id_object FLOAT)")
mycursor.execute("CREATE TABLE flight_air_balloon (specifications_air_balloon_id INT AUTO_INCREMENT PRIMARY KEY, x FLOAT, y FLOAT, Vx FLOAT,  Vy FLOAT)")

mycursor.execute("CREATE TABLE specifications_bird (specifications_bird_id INT AUTO_INCREMENT PRIMARY KEY, mass FLOAT, radius FLOAT, density FLOAT, id_object FLOAT)")
mycursor.execute("CREATE TABLE flight_bird (specifications_bird_id INT AUTO_INCREMENT PRIMARY KEY, x FLOAT, y FLOAT, Vx FLOAT, Vy FLOAT)")
mycursor.execute("CREATE TABLE object_type (object_type_id INT AUTO_INCREMENT PRIMARY KEY, cannonball INT, air_balloon INT, bird INT)")


# Заполнение данными

sql = "INSERT INTO flight_cannonball (x, y, Vx, Vy) VALUES (%s, %s, %s, %s,)"
val = (pointsX[i], pointsY[i], pointsVx[i], pointsVy[i])
mycursor.execute(sql, val)
mydb.commit()

sql = "INSERT INTO specifications_cannonball (mass, radius, density, id_object) VALUES (%s, %s, %s, %s)"
val = (specifications[0], specifications[1], specifications[2], 1)
mycursor.execute(sql, val)
mydb.commit()


# Определение скорости и ускорения на оси x и y

arrayx = [100.6, 152.7, 198.6, 237.4]
arrayy = [83.8, 100.9, 84.4, 21.7]
arraytime = [1.3, 1.7, 1.6]

Vx = [(arrayx[1] - arrayx[0])/arraytime[0],
      (arrayx[2] - arrayx[1])/arraytime[1],
      (arrayx[3] - arrayx[2])/arraytime[2]]
Vy = [(arrayy[1] - arrayy[0])/arraytime[0],
      (arrayy[2] - arrayy[1])/arraytime[1],
      (arrayx[3] - arrayx[2])/arraytime[2]]


ax = [ 0,
      (Vx[1] - Vx[0])/arraytime[1],
      (Vx[2] - Vx[1])/arraytime[2]]

ay = [ 0,
      (Vy[1] - Vy[0])/arraytime[1],
      (Vy[2] - Vy[1])/arraytime[2]]


# Занесение информации о точках полета снаряда в базу данных

i = 0
while i < 3:
	sql = "INSERT INTO inverse_task_flight_cannonball (from_point_to_point, x, y, time, Vx, Vy, ax, ay) VALUES (%s, %s, %s, %s, %s, %s, %s, %s)"
	val = (from_point_to_point[i], arrayx[i], arrayy[i], arraytime[i], Vx[i], Vy[i], ax[i], ay[i])
	mycursor.execute(sql, val)
	mydb.commit()
	i = i + 1
