# Building the app for desktop

run `make debug`

# Building the app into a web app

run `make build -f Makefile.web`

# Running the server (use any web server command of your choice, examples below)

### Using node http-server:

`http-server web`

### Using emscriptens built-in `emrun` command

`emrun web/index.html`

### Using pythons built-in HTTP server `http.server`

`python -m http.server --directory web`
