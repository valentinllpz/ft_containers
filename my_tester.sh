# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    my_tester.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 00:19:36 by vlugand-          #+#    #+#              #
#    Updated: 2022/04/07 23:52:17 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#faire en sorte de pouvoir ajouter les flags fsanitize

g++ -Wall -Werror -Wextra -DSTL map_tests.cpp && ./a.out >> map_stl_output.log
g++ -Wall -Werror -Wextra map_tests.cpp && ./a.out >> map_your_output.log
if diff map_stl_output.log map_your_output.log
then
	echo "MAP TESTS OK"
else
	echo "MAP TESTS KO"
fi
rm -rf *.log