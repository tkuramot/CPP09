NAME := RPN
CXX  := c++
CXXFLAGS := -std=c++98 -Wall -Wextra -Werror -pedantic
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(NAME) $(OBJS)