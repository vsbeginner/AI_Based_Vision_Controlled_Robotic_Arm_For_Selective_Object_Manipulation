from flask import Flask, render_template, request
import streamlit as st
import serial

app = Flask(__name__)

arduino = serial.Serial("COM5", 9600)

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/move", methods=["POST"])
def move():
    direction = request.form["direction"]

    if direction == "left":
        arduino.write(b'B')

    elif direction == "right":
        arduino.write(b'N')

    elif direction == "up":
        arduino.write(b'S')

    elif direction == "down":
        arduino.write(b'X')

    elif direction == "forward":
        arduino.write(b'E')

    elif direction == "back":
        arduino.write(b'Z')

    elif direction == "open":
        arduino.write(b'H')

    elif direction == "close":
        arduino.write(b'G')

    return "OK"

app.run(host="0.0.0.0", port=5000)