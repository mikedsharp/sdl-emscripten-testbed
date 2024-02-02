# Building the app for desktop

run `make debug`

# Running the web app build (a Makefile will handle this soon)

emcc src/thing.cpp src/main.cpp -s WASM=1 -s USE_SDL=2 -s USE_SDL_MIXER=2 -O3 -o web/index.html --preload-file audio/theme.wav

# Running the server (you may use any web server, but this example uses NodeJS http-server)

http-server web
