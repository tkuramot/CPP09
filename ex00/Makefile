CXX			:= c++
CXXFLAGS	:= -g -MMD -MP -Wall -Wextra -Werror -std=c++98
DEBUG_FLAGS		:= -fsanitize=address -fsanitize=bounds
INCLUDE		:= -I src
NAME := btc
SRCDIR		:= src
SRCS		:= $(wildcard $(SRCDIR)/*.cpp)
OBJDIR		:= objs
OBJS		:= $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.cpp=.o))
OBJS_DEBUG	:= $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.cpp=.o.debug))
DEPENDS		:= $(OBJS:.o=.d)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^ $(INCLUDE) $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(OBJDIR)/%.o.debug: $(SRCDIR)/%.cpp
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(INCLUDE) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

-include $(DEPENDS)
