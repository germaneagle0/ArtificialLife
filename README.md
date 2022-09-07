# ArtificialLife
Complex patterns from simple behavior with HTML, Js and WebAssembly. Made so everytime you reopen the page, a new experience.

## To test it out

Run a local server. For an example:
python3 -m http.server
And open the html file in localhost from the port used.

### Without WebAssembly
![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/59073055/188787111-2507b285-cafa-4034-b816-3bbe69018ff7.gif)
### With WebAssembly
https://user-images.githubusercontent.com/59073055/188786599-da756bc0-8afd-483e-82bc-384dc3eb8783.mp4
## To edit the parameter
Change the hello.c, modify the parameters you want then recompile

## To recompile

In the emdsk folder:
emsdk activate latest
emsdk_env.bat

In this folder, run:
emcc -o hello.html hello.c -O3 --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"
