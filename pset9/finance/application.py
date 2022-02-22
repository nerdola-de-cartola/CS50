import os
import sys
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):

    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    stocks = []
    shares = db.execute("SELECT symbol, amount FROM shares WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = cash

    # Convert the SQL query to a better format
    for share in shares:
        stock = assembleStock(share["symbol"], share["amount"])
        stocks.append(stock)
        total += stock["total"]

    return render_template("index.html", stocks=stocks, cash=cash, total=total)

# Return a dictionary with all stock share attributes
def assembleStock(symbol, amount):

    stock = {}
    quote = lookup(symbol)

    stock["symbol"] = symbol
    stock["name"] = quote["name"]
    stock["shares"] = amount
    stock["price"] = quote["price"]
    stock["total"] = quote["price"] * amount

    return stock

# Check if one user exists in the database
def usernameExists(username):

    res = db.execute("SELECT id FROM users WHERE username = ?", username)

    if len(res) == 1:
        return True
    elif len(res) == 0:
        return False
    else:
        return


@app.route("/login", methods=["GET", "POST"])
def login():

    session.clear()

    if request.method == "GET":
        return render_template("login.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        # No input
        if not username or not password:
            return apology("Must provide username and password", 400)

        response = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Invalid username
        if len(response) != 1:
            return apology("Invalid username and/or password", 400)

        # Invalid password
        if not check_password_hash(response[0]["hash"], password):
            return apology("Invalid password", 400)

        # Remember which user has logged in
        session["user_id"] = response[0]["id"]

        return redirect("/")


@app.route("/logout")
def logout():

    # Log out user
    session.clear()

    return redirect("/")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():

    if request.method == "GET":
        return render_template("password.html")

    if request.method == "POST":
        # Old pasword
        password = request.form.get("password")

        # Hash of the old password
        hash_password = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"]

        new_password = request.form.get("new_password")
        confirm_new_password = request.form.get("confirm_new_password")
        message = ""

        # Incorrect password
        if not password or not check_password_hash(hash_password, password):
            message = "Invalid password"

        # Invalid new password
        elif not new_password:
            message = "Invalid new password"

        # Incorrect confirmation
        elif not confirm_new_password or confirm_new_password != new_password:
            message = "Invalid password confirmation"

        if message:
            return apology(message, 400)

        # Redefine password
        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?",
            generate_password_hash(new_password), session["user_id"]
        )

        return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():

    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password_confirm = request.form.get("confirmation")
        message = ""

        if not username:
            message = "Must provide username"

        elif not password:
            message = "Must provide password"

        elif password_confirm != password:
            message = "Must confirm your password"

        if usernameExists(username):
            message = "This username already exists"

        if message:
            return apology(message, 400)

        # Remember which user has logged in
        session["user_id"] = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username, generate_password_hash(password)
        )

        return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        quote_symbol = request.form.get("symbol").upper()
        quote = lookup(quote_symbol)

        # Invalid symbol
        if quote == None:
            return apology("Invalid stock symbol", 400)

        return render_template("quoted.html", quote=quote)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":
        shares = request.form.get("shares")
        quote = lookup(request.form.get("symbol").upper())
        message = ""

        # Try to convert in integer
        try:
            shares = int(shares)
            if shares <= 0 or not isinstance(shares, int):
                message = "Invalid shares amount"

        # If fails
        except:
            message = "Invalid shares amount"

        # Check the stock symbol
        finally:
            if quote == None:
                message = "Invalid stock symbol"

        if message:
            return apology(message, 400)

        total = float(shares) * quote["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Not enough money
        if cash < total:
            return apology("Not enough money to buy", 400)

        # Remove cash from the wallet
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total, session["user_id"])

        # Query how many stonks the user already have
        query = db.execute(
            "SELECT amount FROM shares WHERE user_id = ? AND symbol = ?",
            session["user_id"], quote["symbol"]
        )

        # If already have stocks
        if len(query) == 1:
            current_amount = query[0]["amount"]
            db.execute(
                "UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?",
                shares + current_amount, session["user_id"], quote["symbol"]
            )

        # If is the first stock
        elif len(query) == 0:
            db.execute(
                "INSERT INTO shares (user_id, symbol, amount) VALUES (?, ?, ?)",
                session["user_id"], quote["symbol"], shares
            )

        # Save transaction
        db.execute(
            "INSERT INTO transactions (user_id, symbol, type, amount, price) VALUES (?, ?, ?, ?, ?)",
            session["user_id"], quote["symbol"], "BUY", shares, quote["price"]
        )

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "GET":
        stocks = []
        stocks_query = db.execute("SELECT symbol FROM shares WHERE user_id = ?", session["user_id"])

        # Convert the list of dictionaries in a list of strings
        for stock in stocks_query:
            stocks.append(stock["symbol"])

        return render_template("sell.html", stocks=stocks)

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares_to_sell = request.form.get("shares")
        message = ""

        # Invalid symbol
        if not symbol or lookup(symbol) == None:
            message = "Invalid stock"

        # Invalid amount
        elif not shares_to_sell:
            message = "Invalid amount of shares"

        if message:
            return apology(message, 400)

        shares_to_sell = int(shares_to_sell)
        owned_stocks = db.execute("SELECT symbol, amount FROM shares WHERE user_id = ?", session["user_id"])

        for stock in owned_stocks:

            # Do not have shares enough to sell
            if stock["symbol"] == symbol and stock["amount"] < shares_to_sell:
                message = "Not enough shares to sell"
                return apology(message, 400)

            new_amount = stock["amount"] - shares_to_sell

            # Put cash in the wallet
            new_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
            current_price = lookup(symbol)["price"]
            new_cash += current_price * shares_to_sell
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, session["user_id"])

            # Sell all shares
            if new_amount == 0:
                db.execute(
                    "DELETE FROM shares WHERE user_id = ? AND symbol = ?",
                    session["user_id"], stock["symbol"]
                )

            # Sell a few shares
            elif new_amount > 0:
                db.execute(
                    "UPDATE shares SET amount = ? WHERE user_id = ? AND symbol = ?",
                    new_amount, session["user_id"], stock["symbol"]
                )

            # Save transaction
            db.execute(
                "INSERT INTO transactions (user_id, symbol, type, amount, price) VALUES (?, ?, ?, ?, ?)",
                session["user_id"], stock["symbol"], "SELL", shares_to_sell, current_price
            )

            return redirect("/")

        return apology("You can't sell this stock", 400)


@app.route("/history")
@login_required
def history():

    # Query for user transactions
    transactions = db.execute(
        "SELECT symbol, type, amount, price, data_time FROM transactions WHERE user_id = ?",
        session["user_id"]
    )

    return render_template("history.html", transactions=transactions)


def errorhandler(e):

    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
