from flask import Flask, render_template, request

app = Flask(__name__)

REGISTRANTS = {}

SPORTS = [
	"Dogeball",
	"Flag Football",
	"Soccer",
	"Volleyball",
	"Ultimate Frisbee"
]

@app.route("/")
def index():
	return render_template("index.html", sports = SPORTS)

@app.route("/register", methods = ["POST"])
def register():
	name = request.form.get("name") 
	sports = request.form.get("sports")

	if not name:
		return render_template("error.html", message = "Missing name")
	if not sports:
		return render_template("error.html", message = "Missing sport")
	if sports not in SPORTS:
		return render_template("error.html", message = "Invalid sport")
	
	REGISTRANTS[name] = sports
	return render_template("registrants.html", registrants = REGISTRANTS)
