# Folders and Names
NAME		= ircserv
SRCDIR		= src/
OBJDIR		= obj/
INCLUDES	= inc/
<<<<<<< HEAD
SRC			= main.cpp Client.cpp Server.cpp Channel.cpp
# Compiler options
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98
=======
SRC			= main.cpp \
				Server.cpp
# Compiler options
CC			= c++
CFLAGS		= -std=c++98
#-Wall -Wextra -Werror 
>>>>>>> d0db9bf (epoll: just a copy pasta of a tutorial)

OBJ			= $(patsubst %.cpp, %.o, $(SRC))
OBJS		= $(addprefix ${OBJDIR}, ${OBJ})


all: $(NAME)

$(NAME): $(OBJS)
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Linking "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"

<<<<<<< HEAD
	@$(CC) -o $@ $(OBJS)
=======
	$(CC) -o $@ $(OBJS)
>>>>>>> d0db9bf (epoll: just a copy pasta of a tutorial)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@make create_dir_objs --no-print-directory
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@printf "%-16s" "Compiling "
	@tput sgr0
	@tput setaf 6
	@echo "${@}"

	@$(CC) $(LFLAGS) $(CFLAGS) -c -I $(INCLUDES) -o $@ $<

create_dir_objs:
	@mkdir -p $(OBJDIR)

clean:
	@rm -fr $(OBJDIR)
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "clean done"

fclean: clean
	@rm -rf $(NAME)
	@make print_name --no-print-directory
	@tput bold
	@tput setaf 2
	@echo "fclean done"

re: fclean all

test: all
	./$(NAME)

print_name:
	@tput bold
	@tput setaf 208
	@printf "%-10s " $(NAME)

<<<<<<< HEAD
.PHONY: all clean fclean re test print_name create_dir_objs
=======
.PHONY: all clean fclean re test print_name create_dir_objs
>>>>>>> d0db9bf (epoll: just a copy pasta of a tutorial)
