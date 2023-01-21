UNAME  		:= ${shell uname}
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
ifeq (${UNAME}, Darwin)
		CXXFLAGS += -DDARWIN
endif
CXX				= clang++
RM				= rm -rf
SRC				:= main.cpp vector.cpp stack.cpp map.cpp set.cpp
VPATH			= src/
OBJ_DIR		:= obj/
OBJ				:= ${SRC:%.cpp=${OBJ_DIR}%.o}
OBJ_STL		:= ${SRC:%.cpp=${OBJ_DIR}%.stl.o}
INC				:= -Iinc
INTRA			= src/intra_main.cpp
VISUAL		= src/visualize.cpp

NAME			:= containers_ft
STL				:= containers_stl


##---  Compile FT  ---##
all:					${NAME} stl

${NAME}:			${OBJ}
							${CXX} ${CXXFLAGS} ${OBJ} -o $@

${OBJ_DIR}%.o : %.cpp
							@mkdir -p ${OBJ_DIR}
							${CXX} ${CXXFLAGS} ${INC} -c $< -o $@


##---  Compile STL  ---##
stl:					${STL}

${STL}:				${OBJ_STL}
							${CXX} ${CXXFLAGS} -DSTL ${OBJ_STL} -o $@

${OBJ_DIR}%.stl.o : %.cpp
							@mkdir -p ${OBJ_DIR}
							${CXX} ${CXXFLAGS} -DSTL ${INC} -c $< -o $@


##---  Intra  ---##
intra_ft:
							${CXX} ${CXXFLAGS} ${INC} ${INTRA} -o $@

intra_stl:
							${CXX} ${CXXFLAGS} -DSTL ${INC} ${INTRA} -o $@

intra:				intra_ft intra_stl
							./intra_ft 3 > intra_ft.log
							./intra_stl 3 > intra_stl.log
							diff -u intra_ft.log intra_stl.log


##---  Visualizer  ---##

visualizer:
							${CXX} ${CXXFLAGS} ${INC} ${VISUAL} -o $@

visual:				visualizer
							./visualizer


##---  Clean  ---##
clean:
							${RM} ${OBJ} ${OBJ_STL}

fclean:				clean
							${RM} ${NAME} ${STL} ${NAME}.log ${STL}.log intra_ft intra_stl \
								intra_ft.log intra_stl.log visualizer

re: 					fclean all


##---  Run  ---##
run: 					all
							./${NAME}

run_stl: 			stl
							./${STL}


##---  Test  ---##
diff:					all	# run each binary and save output to files
							./diff.sh

vector:				all
							./diff.sh 10 vector

stack:				all
							./diff.sh 10 stack

map:					all
							./diff.sh 10 map

set:					all
							./diff.sh 10 set


.PHONY : 			all stl intra visual clean fclean re run run_stl diff vector stack map
