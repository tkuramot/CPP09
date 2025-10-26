CXX			:= c++
CXXFLAGS	:= -g -MMD -MP -Wall -Wextra -Werror -std=c++98
DEBUG_FLAGS		:= -fsanitize=address -fsanitize=bounds -DDEBUG_MODE=1
INCLUDE		:= -I src
NAME		:= PMergeMe
NAME_DEBUG	:= PMergeMe_debug
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

debug: $(OBJS_DEBUG)
	$(CXX) -o $(NAME_DEBUG) $^ $(INCLUDE) $(CXXFLAGS) $(DEBUG_FLAGS)

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
	$(RM) $(NAME) $(NAME_DEBUG)

.PHONY: re
re: fclean all

-include $(DEPENDS)
