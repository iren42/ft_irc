# Folders and Names
NAME		= ircserv
SRCDIR		= src/
OBJDIR		= obj/
INCLUDES	= inc/
SRC			= main.cpp \
				Client.cpp\
				Server.cpp\
				Channel.cpp\
				actions/parse_action.cpp\
				actions/action_who.cpp\
				actions/action_cap.cpp\
				actions/action_nick.cpp\
				actions/action_user.cpp\
				actions/action_join.cpp\
				actions/action_part.cpp\
				actions/action_privmsg.cpp\
				actions/action_help.cpp\
				actions/action_quit.cpp\
				actions/action_list.cpp\
				actions/action_whois.cpp\
				actions/action_names.cpp\
				actions/action_invite.cpp\
				actions/action_kick.cpp\
				actions/action_mode.cpp\
				actions/action_topic.cpp\
				actions/action_pass.cpp\
				actions/action_notice.cpp\
				actions/action_ping.cpp\



# Compiler options
CC			= c++
CFLAGS		= -std=c++98 -Wall -Wextra -Werror -g

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
	@mkdir -p $(OBJDIR)actions/


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
