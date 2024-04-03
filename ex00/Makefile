NAME := btc
CXX  := c++
CXXFLAGS := -std=c++98 -Wall -Wextra -Werror -pedantic
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(NAME) $(OBJS)