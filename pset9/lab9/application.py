import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():

    # Insert a new birthday into the database
    if request.method == "POST":
        # Get input from the form
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Input data into the database
        if name and month and day:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?);", name, month, day)

        # Reload page
        return redirect("/")

    # Fill the html table with birthdays of the database
    else:
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays = birthdays)


