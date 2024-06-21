
# global variables

PROJECT_NAME = onebrc

SOURCE_DIR = source/
TARGET_DIR = build/

CXX = g++
CXX_ARGS = -std=c++20 -Wall -Werror -O3

# target commands

all: $(PROJECT_NAME)

clean:
	rm -rf $(TARGET_DIR)

$(PROJECT_NAME): $(SOURCE_DIR)$(PROJECT_NAME).cpp
	mkdir -p $(TARGET_DIR)$(PROFILE_DIR)
	$(CXX) $(CXX_ARGS) $(CXX_FLAGS) $(SOURCE_DIR)$(PROJECT_NAME).cpp -o $(TARGET_DIR)$(PROFILE_DIR)$(PROJECT_NAME)

# profile commands

nochrono: CXX_FLAGS = -DNO_CHRONO
nochrono: PROFILE_DIR = nochrono/
nochrono: $(PROJECT_NAME)
