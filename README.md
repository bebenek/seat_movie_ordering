# Movie Reservation Tool

This is a sample project showcasing a microservice implemented in C++ using a CLI as the frontend. The project utilizes Conan package management for dependencies.
Service shows in simple way how async reservastion of movies could be done.

## Prerequisites

- C++ compiler (GCC or Clang)
- CMake
- Conan package manager

## Getting Started

1. Clone the repository:

   ```shell
   git clone git@github.com:bebenek/seat_movie_ordering.git
   cd seat_movie_ordering
   ```
2. CLI build:
   1. Build the project:
      ```shell
      conan profile detect
      conan install . --build=missing
      mkdir build
      cd build
      cmake ..
      cmake --build .
      ```
   2. Run the microservice:
      ```shell
      ./movie_reservation <port> <filename>
      ```
   3. Test execution
      ```shell
      ctest
      ```
   3. Doxygen generation
      ```shell
      doxygen Doxyfile
      ```
      after generation you can find documentation under docs/html and docs/latex directories
2. Docker build:
   1. Build the project:
      ```shell
      docker build -t movie_reservation .
      ```
   2. Run the microservice:
      ```shell
      docker run -p 8080:8080 -d movie-order /app/build/movie_reservation 8080 app/example_input_file.txt
      ```

## API description
There are 4 allowed requests for this BE:
1. looking for all movies:
   ```
   {}
   ```
   The response always will be list of available movies
2. looking for theatres for particular movie:
   ```json
   {
    "movie": "<movie_name>" // required
   }
   ```
   Response will be list of theatres or error:
   ```json
   {"error_message":"Movie not found"}
   ```
3. looking for seats for movie in theater:
   ```json
   {
    "movie": "<movie_name>", // required
    "theater": "<theater_name>" // required
   }
   ```
   Response will be list of available seats or error:
   ```json
   {"error_message":"Movie or theater not found"}
   ```
4. Seat reservation:
   ```json
   {
    "movie": "<movie_name>", // required
    "theater": "<theater_name>", // required
    "seat": "<seat_id>" // required
   }
   ```
   Response will be similar to 3. but with boolean indicator if reservation was successfull or error message if cannot match:
   ```json
   {"error_message":"Movie or theater not found"}
   ```

## Input file format
The file format should be that each line is separate json for example:
```json
{"movie": "movie_1", "theater": "theather_1", "seat": ["A1", "A2", "A3", "A4"]}
{"movie": "movie_1", "theater": "theather_2", "seat": ["B1", "B2", "B3", "B4"]}
```
Seats should be within A1-E4

## Example Usage
Once the microservice is running, you can interact with it through the command-line interface (CLI). For example on the other console you can execute:
```shell
nc -v localhost 8080 ../example_input_file.txt
```
example input file exists in this repository so it can be used.

1. enter empty json to list movies:
   ```json
   {}
   {"movies":["m1","m2"]}
   ```
2. Pick up a movie:
   ```json
   {"movie":"m1"}
   {"movie":"m1","theaters":["t1","t2"]}
   ```
3. Pick up a theater:
   ```json
   {"movie":"m1", "theater":"t1"}
   {"movie":"m1","theater":"t1","seats":["C3","C4","D3","D4","E3","E4"]}
   ```
4. No you can pick a seat to reserve:
   ```json
   {"movie":"m1", "theater":"t1", "seat":"C3"}
   {"reserved_successfully":true,"movie":"m1","theater":"t1","seats":["C4","D3","D4","E3","E4"]}
   ```
   reserved successfully indicates if you were able to reserve and seats output is reduced by the seat used for request.
5. If you pick up the same seat again:
   ```json
   {"movie":"m1", "theater":"t1", "seat":"C3"}
   {"reserved_successfully":false,"movie":"m1","theater":"t1","seats":["C4","D3","D4","E3","E4"]}
   ```
   you will receive that reservation was not successfull and notghing will happen.



