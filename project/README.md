# Questionary

#### Video Demo:  <https://youtu.be/dFnOC2xQFuI>

#### Description:
My web app is called "Questionary" and its purpose in life is to be an online platform where people can share anonymous questions in private rooms.
The app was created with teachers in mind who need to teach online during the pandemic. So, using the app, students can share their questions anonymously and the teacher can answer them in the zoom lesson. But the app can serve many other uses, such as for business teams when they need to ask questions privately or content creators when they want to answer fan questions

#### Pages:
##### Index:
In the home page you can access a room by typing your id
![Home page](https://live.staticflickr.com/65535/51671106086_c49cc54ab7_h.jpg)

##### Create room:
In the create room page you are able to create your own room by typing a password
![Create room page](https://live.staticflickr.com/65535/51671787224_99342ada1f_k.jpg)

##### Room:
On one of the room pages you can send your own questions to everyone else or if you are the owner of this room you can also mark read or delete any question in the room.
![Room page](https://live.staticflickr.com/65535/51670304002_607d674118_k.jpg)

##### Error:
This is a page you might not like. It is used whenever something goes wrong, like a server error (500) or a not found (404) or even when you enter the wrong password or room id
![Error page](https://live.staticflickr.com/65535/51670304007_5e70979ef2_k.jpg)

#### Stack:
Flask, Jinja2, SQLite3, Python, SQL, HTML, CSS, JavaScript

#### How it works:

##### app.py
The app works by defining routes using flask in the app.py file where each function represents a route

##### questionary.db
It's the database for storing rooms and questions

#### static/scripts/modal.js
Open and close the form to delete or check questions

##### static/scripts/main.js
Populate the HTML form depending if it's a delete action or an check action

##### static/styles
It's important to now that every page has one css file and the global css file

##### templates/layouts
This directory is for layouts that are going to be extended into other templates

##### templates/pages
This directory contains the pages that will be rendered by the routes.

##### templates/parts
This directory contains parts that are going to be conditionally include into pages

##### application.py
This is the main file in this project, all Python code was written here. In this file we define the routes, methods, parameters and settings of the application

##### questionary.db
This is the database of our site and he is used to storering the rooms and the question

##### requirements.txt
This file is used to keep track of the dependencies of the project and to quick setup the environment installing dependencies

#### Thanks:
The ideia was first created during a javascript online course called "nlw (next level week)" from [Rocketseat](https://github.com/Rocketseat) and I use this idea and visual concept but the role code, templates and logic was build by my [self](https://www.github.com\nerdola-de-cartola)

#### Sorry:
1. Sorry for my bad English, I may have used Google Translate
2. Sorry for the latency, the site uses a lot of images and I have no idea how to optimize them