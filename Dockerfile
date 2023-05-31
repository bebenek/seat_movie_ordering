# Start with a base image that has gcc installed
FROM gcc:10

# Set the working directory
WORKDIR /app

# Install Python and pip
RUN apt-get update && \
    apt-get install -y python3 python3-pip

RUN apt-get install -y build-essential cmake --no-install-recommends
# Install Conan
RUN pip3 install conan

# Copy the project files into the docker container
COPY . .

# Install dependencies with Conan
# RUN conan profile detect && conan install . --build missing --profile:build=default --profile:host=default

RUN conan profile detect && conan install . --build=missing
RUN mkdir -p build && cd build && cmake .. && cmake --build .
# CMD ["bash", "-c", "while true; do sleep 1; done"]
# # # Build the project
# RUN mkdir build && \
#     cd build && \
#     cp conanbuildinfo.cmake build/ && \
#     cmake .. && \
#     cmake --build .
