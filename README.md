# Room Climate Logger

A full-stack web app that logs the temperature and humidity of my room, so I can see how it changes through the day. I made it because my room gets very humid and I wanted to track it instead of guessing.

**Live app:** https://dashboard.render.com/web/srv-db8mlg689jmc73eo9ih0/deploys/dep-db8mot7avr4c73dh4jng

Note: the app is on a free host, so if nobody has used it for a while, the first load can take about a minute to wake up.

## What the app does

- Saves readings (temperature, humidity, and an optional note)
- Shows the latest reading and the full history on a web page
- Lets me edit the note of a reading
- Lets me delete a reading I don't want

## Tech stack

- Node.js and Express for the backend
- MongoDB Atlas with Mongoose for the database
- Plain HTML, CSS, and JavaScript for the front end
- Git and GitHub for version control
- Render for hosting

## API routes

| Action | Route | CRUD |
|---|---|---|
| Save a new reading | POST /api/readings | Create |
| Get all readings | GET /api/readings | Read |
| Get the newest reading | GET /api/readings/latest | Read |
| Edit a reading's note | PUT /api/readings/:id | Update |
| Delete a reading | DELETE /api/readings/:id | Delete |

## How to run it locally

You need Node.js installed and a free MongoDB Atlas cluster.

1. Clone the repository:
   `git clone https://github.com/brianmoulic/room-climate-logger.git`
2. Go into the folder: `cd room-climate-logger`
3. Install the packages: `npm install`
4. Create a file named `.env` in the main folder with these two lines:
   - `PORT=3000`
   - `MONGODB_URI=mongodb+srv://mbmoulic_db_user:h00RaaYJ8rXzSeHR@cluster0.h4pbjpd.mongodb.net/`
5. Start the app: `npm start`
6. Open `http://localhost:3000` in your browser.

The `.env` file is not uploaded to GitHub because it has my private database password.

## Bonus extensions

- App Inventor mobile app: not done yet
- Arduino (simulated sensor): not done yet

## Author

Brian Moulic, CITE 006A, T.I.P. Manila
