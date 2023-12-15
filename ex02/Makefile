CXX			:= c++
CXXFLAGS	:= -g -MMD -MP -Wall -Wextra -Werror -std=c++98
DEBUG_FLAGS		:= -fsanitize=address -fsanitize=bounds
INCLUDE		:= -I include
NAME		:= a.out
NAME_DEBUG	:= debug.a.out
SRCDIR		:= src
SRCS		:= \
	src/main.cpp
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

.PHONY: debug
debug: $(NAME_DEBUG)

$(NAME_DEBUG): $(OBJS_DEBUG)
	$(CXX) -o $@ $^ $(INCLUDE) $(CXXFLAGS) $(DEBUG_FLAGS)

$(OBJDIR)/%.o.debug: $(SRCDIR)/%.cpp
	@ mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) $(INCLUDE) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_DEBUG)

.PHONY: re
re: fclean all

cppfile:
	find src -name "*.cpp" | sed 's/\.\///g' | awk '{print "\t"$$0" \\"}' | sed '$$s/ \\//' | pbcopy

-include $(DEPENDS)
