# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    my_tester.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 00:19:36 by vlugand-          #+#    #+#              #
#    Updated: 2022/03/29 23:22:20 by vlugand-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#faire en sorte de pouvoir ajouter les flags fsanitize

g++ -Wall -Werror -Wextra -DSTL map_tests.cpp && ./a.out >> map_stl_output.log
g++ -Wall -Werror -Wextra map_tests.cpp && ./a.out >> map_your_output.log
diff map_stl_output.log map_your_output.log
rm -rf *.log