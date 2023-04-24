#Compiler and Linker
CC          = cc

#Target .exe
SERVER		= server
CLIENT		= client

#Directories, Source, Objects, Lib
SRCS_DIR		= srcs/
OBJS_DIR		= objs/
LIB_DIR			= libft/

#Sub-Directories, Server, Client
SV_SRCS_DIR			= $(SRCS_DIR)server/
CL_SRCS_DIR			= $(SRCS_DIR)client/
SV_OBJS_DIR			= $(OBJS_DIR)server/
CL_OBJS_DIR			= $(OBJS_DIR)client/

#Flags, Libraries and Includes
INCLUDES	= -I ./inc/
CFLAGS		= -Wall -Werror -Wextra
LIBFT		= $(LIB_DIR)libft.a
LDFLAGS 	= -L $(LIB_DIR) -lft

#Colors
RESET		= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[0;93m
BLUE		= \033[0;34m
PURPLE		= \033[1;35m
CYAN		= \033[0;96m
WHITE		= \033[0;97m

# Inverted, i.e. colored backgrounds
IGREY		= \033[40m
IRED		= \033[41m
IGREEN		= \033[42m
IYELLOW		= \033[43m
IBLUE		= \033[44m
IPURPLE		= \033[45m
ICYAN		= \033[46m
IWHITE		= \033[47m

#Counter
COUNT_SV	= 0
COUNT_CL	= 0

#---------------------------------------------------------------------------------
#Do not edit below this line
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
#Source and object files
SV_SRCS		= $(wildcard $(SV_SRCS_DIR)*.c)
CL_SRCS		= $(wildcard $(CL_SRCS_DIR)*.c)

#Object files
SV_OBJS		= $(addprefix $(SV_OBJS_DIR), $(notdir $(SV_SRCS:.c=.o)))
CL_OBJS		= $(addprefix $(CL_OBJS_DIR), $(notdir $(CL_SRCS:.c=.o)))

#---------------------------------------------------------------------------------

#Default Make
all: $(LIBFT) dir $(SERVER) $(CLIENT)

#Compile Server files
$(SERVER): $(SV_OBJS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	@echo "]"
	@echo "$(GREEN)./server created ->$(RESET)"
	@echo "$(COUNT_SV) files compiled"
	@echo "____________________\n"

$(SV_OBJS_DIR)%.o: $(SV_SRCS_DIR)%.c
	@if [ $(COUNT_SV) = 0 ]; then echo -n "$(GREEN)Compiling Server files$(RESET)\n["; fi
	@echo -n "$(YELLOW)$(IGREY).$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@
	@$(eval COUNT_SV=$(shell echo $$(($(COUNT_SV)+1))))

$(LIBFT):
	@make --no-print-directory all -C $(LIB_DIR)

#Compile Client files
$(CLIENT): $(CL_OBJS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	@echo "]"
	@echo "$(GREEN)./client created ->$(RESET)"
	@echo "$(COUNT_CL) files compiled"
	@echo "____________________\n"

$(CL_OBJS_DIR)%.o: $(CL_SRCS_DIR)%.c
	@if [ $(COUNT_CL) = 0 ]; then echo -n "$(GREEN)Compiling Client files$(RESET)\n["; fi
	@echo -n "$(YELLOW)$(IGREY).$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@
	@$(eval COUNT_CL=$(shell echo $$(($(COUNT_CL)+1))))

#Directories
dir: $(OBJS_DIR) $(SV_OBJS_DIR) $(CL_OBJS_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(SV_OBJS_DIR):
	@mkdir -p $(SV_OBJS_DIR)

$(CL_OBJS_DIR):
	@mkdir -p $(CL_OBJS_DIR)

#Clean only Object files
clean:
	@rm -rf $(OBJS_DIR)
	@make --no-print-directory clean -C $(LIB_DIR)

#Full Clean, Object and Binary files
fclean: clean
	@rm -f $(SERVER)
	@rm -f $(CLIENT)
	@rm -f $(LIBFT)

#Remake
re: fclean all

#Non-File Targets
.PHONY: all bonus clean fclean re
