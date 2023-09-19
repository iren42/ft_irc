# Folders and Names
NAME		= ircserv
SRCDIR		= src/
OBJDIR		= obj/
INCLUDES	= inc/
SRC			= main.cpp \
				Server.cpp
# Compiler options
CC			= c++
CFLAGS		= -std=c++98 
#-Wall -Wextra -Werror 

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

	@$(CC) -o $@ $(OBJS)

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

.PHONY: all clean fclean re test print_name create_dir_objs
