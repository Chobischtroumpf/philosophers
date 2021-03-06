# ================================ VARIABLES ================================= #

NAME    = philo_one
CXX     = gcc
CXXFLAGS  = -Wall -Werror -Wextra

SRCDIR  = ./
INCDIR  = includes/
OBJDIR  = objs/

CXXFLAGS	+= -I $(INCDIR)

SRCS    =		main.c			\
				philosophers.c	\
				init_struct.c	\
				print.c			\
				utils.c			\
				utils2.c

SRC             := $(notdir $(SRCS)) #                                  Files only
OBJ             := $(SRC:.c=.o)       #                                       Files only
OBJS    := $(addprefix $(OBJDIR), $(OBJ)) #             Full path
CSRCS   := $(addprefix ../, $(SRCS)) #                  Compiler

GR      = \033[32;1m #  Green
RE      = \033[31;1m #  Red
YE      = \033[33;1m #  Yellow
CY      = \033[36;1m #  Cyan
RC      = \033[0m #     Reset Colors

# ================================== RULES =================================== #

all : $(NAME)

#       linking
$(NAME) : $(OBJS)
		@printf "$(YE)&&& Linking $(OBJ) to $(NAME)$(RC)"
		$(CXX) -lpthread $(CXXFLAGS) -o $(NAME) $(OBJS)

#       compiling
$(OBJS) : $(SRCS)
		@printf "$(GR)+++ Compiling $(SRC) to $(OBJ)$(RC)"
		@mkdir -p $(OBJDIR)
		@cd $(OBJDIR) && $(CXX) $(CXXFLAGS) -I ../$(INCDIR) -c $(CSRCS)

#       runnng

run : $(NAME)
		@echo "$(CY)>>> Running $(NAME)$(RC)"
		./$(NAME)
#       cleaning
clean :
		@echo "$(RE)--- Removing $(OBJ)$(RC)"
		@rm -fd $(OBJS) $(OBJDIR)

fclean : clean
		@echo "$(RE)--- Removing $(NAME)$(RC)"
		@rm -f $(NAME)

re : fclean all

debug :
		@echo "SRCS $(SRCS)"
		@echo "SRC $(SRC)"
		@echo "OBJS $(OBJS)"
		@echo "OBJ $(OBJ)"
		@echo "CSRCS $(CSRCS)"
		@echo "CFLAGS $(CFLAGS)"

.PHONY  = all run clean fclean re debug
