import os
import time

from cs50 import SQL
from flask import Flask, flash, redirect, jsonify, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # pull user cash, boughr and sold shares from db
    bought_shares = db.execute(
        'SELECT symbol, sum(shares) FROM bought_sold WHERE bought_sold = "bought" AND user_id = ? GROUP BY symbol', session['user_id'])
    sold_shares = db.execute(
        'SELECT symbol, sum(shares) FROM bought_sold WHERE bought_sold = "sold" AND user_id = ? GROUP BY symbol', session['user_id'])
    user_cash = db.execute('SELECT * FROM users WHERE id = ?', session['user_id'])[0]['cash']

    portfolio = []  # each item is going to be stock_values dict containing symbol name price shares total
    portfolio_cash = 0  # cash of whole portfolio, will me summed for each stock

    # shares in portfolio are bought minus sold
    for bought in bought_shares:
        bought['symbol']
        stock_values = lookup(bought['symbol'])
        in_sold = False
        for sold in sold_shares:
            if bought['symbol'] == sold['symbol']:
                stock_values.update({'shares': bought['sum(shares)'] - sold['sum(shares)']})
                in_sold = True
                break
        if not in_sold: # if any share of that stock was sold shares are only bought ones
            stock_values.update({'shares': bought['sum(shares)']})

        # calculate total of stock, sum to total of portfolio, format dolars and append to list of stock_values
        stock_values.update({'total': stock_values['shares'] * stock_values['price']})
        portfolio_cash += stock_values['total']
        stock_values['total'] = usd(stock_values['total'])
        stock_values['price'] = usd(stock_values['price'])

        if stock_values['shares'] != 0:
            portfolio.append(stock_values)

    # total of portlofio_cash + user_cash, format dolars
    user_total = usd(user_cash + portfolio_cash)
    user_cash = usd(user_cash)
    portfolio_cash = usd(portfolio_cash)

    return render_template("index.html", user_cash=user_cash, portfolio_cash=portfolio_cash, user_total=user_total, portfolio=portfolio)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # get form
        quote = lookup(request.form.get("symbol"))

        # Ensure symbol is valid
        if not quote:
            return apology("invalid symbol")
        quote['price'] = usd(quote['price'])
        return render_template("quoted.html", quote=quote)
    return render_template("quote.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # get form
        quote = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")

        # Ensure symbol is valid
        if not quote:
            return apology("invalid symbol")

        # Ensure shares is valid
        try:
            shares = int(shares)
            if shares < 1:
                raise ValueError
        except ValueError:
            return apology("shares must be at an integer >= 1")

        # Ensure user has cash to complete transaction
        user_cash = db.execute('SELECT * FROM users WHERE id = ?', session['user_id'])[0]['cash']
        total_price = quote['price'] * shares
        if user_cash < total_price:
            return apology('must have at least' + ' ' + usd(total_price))

        # Register buy in bought_sold and update users cash
        db.execute('INSERT INTO bought_sold (user_id, bought_sold, symbol, shares, price, date_time) VALUES(?, ?, ?, ?, ?, ?)',
session['user_id'], 'bought', quote['symbol'], shares, quote['price'], time.time())

        db.execute('UPDATE users SET cash = cash - ? WHERE id = ?', total_price, session['user_id'])

        return redirect("/")
    return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Get symbol and shares from form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol is valid
        if not symbol:
            # Case nothing sumbmitted symbol is None
            # Lookup was raising an error receiving None
            symbol = ""
        quote = lookup(symbol)
        if not quote:
            return apology("invalid symbol")

        # Ensure shares is valid
        try:
            shares = int(shares)
            if shares < 1:
                raise ValueError
        except ValueError:
            return apology("shares must be at an integer >= 1")

        # Ensure user has shares to sell
        bought = db.execute('SELECT sum(shares) FROM bought_sold WHERE user_id = ? AND bought_sold = ? AND symbol = ?',
        session['user_id'], 'bought', quote['symbol'])[0]['sum(shares)']

        sold = db.execute('SELECT sum(shares) FROM bought_sold WHERE user_id = ? AND bought_sold = ? AND symbol = ?',
        session['user_id'], 'sold', quote['symbol'])[0]['sum(shares)']

        if bought == None:
            bought = 0
        if sold == None:
            sold = 0
        if shares > bought - sold:
            return apology(f'Must have at least {shares} shares')

        # Register sell in bought_sold and update users cash
        db.execute('INSERT INTO bought_sold (user_id, bought_sold, symbol, shares, price, date_time) VALUES(?, ?, ?, ?, ?, ?)',
        session['user_id'], 'sold', quote['symbol'], shares, quote['price'], time.time())

        db.execute('UPDATE users SET cash = cash + ? WHERE id = ?', quote['price'] * shares, session['user_id'])

        return redirect("/")

    stocks = []
    bought_shares = db.execute(
        'SELECT symbol, sum(shares) FROM bought_sold WHERE bought_sold = "bought" AND user_id = ? GROUP BY symbol', session['user_id'])
    sold_shares = db.execute(
        'SELECT symbol, sum(shares) FROM bought_sold WHERE bought_sold = "sold" AND user_id = ? GROUP BY symbol', session['user_id'])
    for bought in bought_shares:
        bought['symbol']
        quote = lookup(bought['symbol'])
        in_sold = False
        for sold in sold_shares:
            if bought['symbol'] == sold['symbol']:
                quote.update({'shares': bought['sum(shares)'] - sold['sum(shares)']})
                in_sold = True
                break
        if not in_sold:  # If any share of that stock was sold shares are only bought ones
            quote.update({'shares': bought['sum(shares)']})
        if quote['shares'] != 0:
            stocks.append(quote)
    return render_template("sell.html", stocks=stocks)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM bought_sold WHERE user_id = ?", session['user_id'])
    for transaction in history:
        transaction['price'] = usd(transaction['price'])
        transaction['date_time'] = time.ctime(transaction['date_time'])

    return render_template("history.html", history=history)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register User"""
    if request.method == "POST":

        # Get form inputs
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username")

        # Ensure username don't exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) != 0:
            return apology("username already exists")

        # Ensure password is not blank and matches confirmation
        if not password:
            return apology("must provide password")

        if password != confirmation:
            return apology("password must match confirmation")

        # Save username and hashed password to db, retirect to /
        hashedPassword = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashedPassword)
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("register.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")