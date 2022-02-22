# For handle SQL querys
from cs50 import SQL
# For generate random id's
from random import randrange
# For handle routes, methods and jinja templates
from flask import Flask, flash, redirect, render_template, request, url_for
# For handle errors
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
# For handle hashed passwords
from werkzeug.security import check_password_hash, generate_password_hash


# Configure application
app = Flask(__name__, static_url_path="")

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///questionary.db")


@app.route("/", methods=["GET", "POST"])
def index():

    if request.method == "GET":
        return render_template("pages/index.html", parts=["enter-room"])

    elif request.method == "POST":
        # Query for the room
        room_id = db.execute(
            "SELECT id FROM rooms WHERE id = ?",
            request.form.get("room_id")
        )

        # If the room doesn't exist
        if len(room_id) != 1:
            return apology("this room doesn't exist")

        # Clean the query
        room_id = room_id[0]["id"]

        return redirect(url_for("room", room_id=room_id))


@app.route("/create-room", methods=["GET", "POST"])
def createRomm():

    if request.method == "GET":
        return render_template("pages/index.html", parts=["create-room"])

    elif request.method == "POST":
        password = request.form.get("password")

        if password:
            # Generate new hash password
            hash_password = generate_password_hash(password)

            # Generate random id
            room_id = randrange(100000, 999999)

            # Create new room
            db.execute("INSERT INTO rooms (id, hash) VALUES (?, ?)", room_id, hash_password)

            return redirect(url_for("room", room_id=room_id))

@app.route("/room/<room_id>", methods=["GET", "POST"])
def room(room_id):

    res = db.execute("SELECT id FROM rooms WHERE id = ?", room_id)

    if len(res) != 1:
        return apology("this room doesn't exist")

    if request.method == "GET":
        # Query for questions
        questions = db.execute("SELECT id, title, read FROM questions WHERE room_id = ?", room_id)

        return render_template("pages/room.html", room_id=room_id, questions=questions)

    elif request.method == "POST":
        title = request.form.get("question")

        if title:
            # Create new question
            db.execute("INSERT INTO questions (title, room_id) VALUES (?, ?)", title, room_id)

        return redirect(request.referrer)


@app.route("/room/<room_id>/question/<question_id>/<action>", methods=["POST"])
def question(room_id, question_id, action):

    room_hash = db.execute("SELECT hash FROM rooms WHERE id = ?", room_id)[0]["hash"]

    # If the user enters the wrong password
    if not check_password_hash(room_hash, request.form.get("password")):
        return apology("invalid password")

    # For delete questions
    if action == "delete":
        db.execute("DELETE FROM questions WHERE id = ?", question_id)
        return redirect(request.referrer)

    # For read questions
    if action == "check":
        db.execute("UPDATE questions SET read = 1 WHERE id = ?", question_id)
        return redirect(request.referrer)


# Render apology paga
def apology(message, code=400):

    return render_template("pages/apology.html", message=message, code=code)


def errorhandler(e):

    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)