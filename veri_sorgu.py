import sqlite3, os

dosya = 'vt.sqlite'
dosya_mevcut = os.path.exists(dosya)

vt = sqlite3.connect(dosya)
im = vt.cursor()

im.execute("""SELECT * FROM mqtt_depo""")

veriler = im.fetchall()
print(veriler)
