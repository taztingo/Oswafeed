# Oswafeed

Oswafeed (Oswald the Rabbit Feed) is basic application that pulls data 
from mlb's web api and renders all the recap photos on a cool background. It's THE application
that tried its best to make it to the spotlight. The goal was to be able to navigate between
photos and view a title and subtitle. Unfortunately, because of time constraints the 
photos are rendered, but cannot be navigated. It's left to the user to imagine what lies 
beyond the application boundaries.

The application makes use of opengl, glfw3, and glad to render the application.
It uses the multi-platform Poco library to handle web requests. It's pretty neat.

## Building

Oswafeed was built in Visual Studio 2019 and includes all the headers, dlls, libs
, and other resources that are required to build it on Windows 10 64-bit. You
will have to install a rootcert.pem to get Poco to correctly handle https. You
just have to build the solution for release or debug. It may take some time
to pull the data from the web

## Features

- Uses opengl, glfw3, and glad for drawing
- Uses the supplied image as the background
- Makes web requests using Poco NET
- Parses web requests using Poco JSON
- Renders the recap photos in a scrollbar

## Planned but not met / Issues

- Keyboard input does not correctly update the scrollbar
- Item selection missing which displays captions, border, and increased image size missing
- ItemService and renderables can be refactored, its mainly prototype code
- Missing a cache or efficient way to pull content files
- Sliding Window to pull images behind the scenes
- ItemService was planned to be async (Maybe ActiveObject pattern?)
- Entering a date to pull files
- Changing the heap allocated data to stack data in some places
- Making use of move operators for some portions

## Notes
- It may take a few seconds to pull data from the web. Issues
with the rootcert.pem can slow this down.

## License
[MIT](https://choosealicense.com/licenses/mit/)