cmake_minimum_required(VERSION 3.16.3)

# Quoted and Unquoted arguments with examples

#---------------------------+-----------------+-----------------+-------------------+
# Set Command               |    Value of VAR | message(${VAR}) | message("${VAR}") |
#---------------------------+-----------------+-----------------+-------------------+
# set (VAR  aa bb cc)       |   aa;bb;cc      |     aabbcc      |   aa;bb;cc        |
# set (VAR  aa;bb;cc)       |   aa;bb;cc      |     aabbcc      |   aa;bb;cc        |
# set (VAR "aa" "bb" "cc")  |   aa;bb;cc      |     aabbcc      |   aa;bb;cc        |
# set (VAR "aa bb cc")      |   aa bb cc      |     aa bb cc    |   aa bb cc        |
# set (VAR "aa;bb;cc")      |   aa;bb;cc      |     aabbcc      |   aa;bb;cc        |
#---------------------------+-----------------+-----------------+-------------------+

# * When we use arguments without Quotes, CMake combines the arguments to make a list of arguments which are
#   seperated by ';', like aa;bb;cc
# * ${VAR}      - prints the list without ';'
# * "${VAR}"    - In this case, CMake doesn't look what's inside the quotes and directly prints it.


# ** CASE 1: set (VAR aa bb cc) ** 
set (VAR aa bb cc)
message (${VAR})                #  prints aabbcc
message ("${VAR}")              #  prints aa;bb;cc

# ** CASE 2: set VAR to a list directly VAR = aa;bb;cc
set (VAR aa;bb;cc)
message (${VAR})                # prints aabbcc   (understands and prints list)
message ("${VAR}")              # prints aa;bb;cc (whatever is the input)

# ** CASE 3: set VAR to "aa" "bb" "cc", that is VAR = "aa";"bb";"cc"
set (VAR "aa" "bb" "cc")
message (${VAR})                # prints aabbcc   (understands and prints list)
message ("${VAR}")              # prints aa;bb;cc (whatever is the input)

# ** CASE 4: set VAR to "aa bb cc", VAR can't be interpreted as list, but VAR is a string
set (VAR "aa bb cc")            # VAR is a list of one single string. 
message (${VAR})                # prints aa bb cc, string 
message ("${VAR}")              # prints aa bb cc   (whatever is the input, which is string)

# ** CASE 5: set VAR to "aa bb cc", VAR can't be interpreted as list, but VAR is a string
set (VAR "aa;bb;cc")            # VAR is a list of one single string. 
message (${VAR})                # prints aabbcc, string 
message ("${VAR}")              # prints aa;bb;cc   (whatever is the input, which is string)

#=====================================================================================
# 18. Manipulating Variables 
#=====================================================================================
set (NAME Alice) 					# Sets NAME to Alice
set (Alice Bob)						# Sets Alice to Bob

message (${NAME}) 					# prints 'Alice'
message (${${NAME}}) 				# prints 'Bob'

message (NAME ${NAME} ${${NAME}}) 	# prints NAMEAliceBob
message ("NAME ${NAME} ${${NAME}}")	# prints NAME Alice Bob

set (NAMEAliceBob Charlie)			# Sets NAMEAliceBob to Charlie
message (${NAME${NAME}${${NAME}}})	# prints Charlie
# message (${NAME ${NAME} ${${NAME}}})# Error !!

# Every variable in CMake is of string type.
set (NAME 3.14)						# sets value of NAME to "3.14" (string)
set (3.14 Bob) 						# sets value of (string) 3.14 to Bob
message (${NAME}) 					# Prints 3.14 (string)
message (${${NAME}})				# Prints Bob

# Note :
#* 	Variable names are surrounded by curly brackets while dereferencing,
#	like ${NAME}
#* 	If you happen to see an expression enclosed inside a angled brackets,
#	do not confuse it with the variables, these expressions are called generator
#	expressions, like $<TARGET_FILE:library>

#=====================================================================================
# 19. Lists & Strings
#=====================================================================================

# list() command operates on the lists
# list(<sub command> <name of the list> ... ... <return variable>)
# @ Subcommand - tells which operation needs to be performed 
#				APPEND, INSERT, FILTER, GET, JOIN are some of the subcommand that you see
#				very frequently.
# @ name of the list which needs to be operated.
# @ 3rd and the subsequent commands are the arguments of the subcommand.
# 	If a list subcommand is returning a value after performing some operation on the
# 	given list, then the last argument is the output variable.
# 

# 1) Create a list of 8 items using set command
#	@ Note : Indexing starts from 0
set (VAR a b c;d "e;f" 2.718 "Hello, there !")
#		 0 1 2 3  4 5   6          7
#       -8-7-6-5 -4-3  -2		  -1
message (${VAR})		# prints abcdef2.718Hello, there !

# 2) Operations -- APPEND, REMOVE_ITEM, REMOVE_AT, INSERT, REVERSE, REMOVE_DUPLICATES, SORT
#

# 2a) APPEND
list (APPEND VAR 1.6 XX) 	# Append 2 items 1.6 and XX to list VAR 
message (${VAR})			# prints abcdef2.718Hello, there !1.6XX
# List VAR is now - 
# 		 a b c;d "e;f" 2.718 "Hello, there !" 1.6 XX
#		 0 1 2 3  4 5   6          7
#      -10-9-8-7 -6-5  -4		  -3          -2  -1

# 2b) REMOVE_AT
list (REMOVE_AT VAR 2 -3) 	# remove 2 items from position 2 and -3 from the list
message (${VAR})			# prints abdef2.7181.6XX ; Items c and 'Hello, there !'  removed.
# List VAR is now - 
# 		 a b d "e;f" 2.718 1.6 XX
#		 0 1 2   3     4    5   6
#       -7-6-5  -4    -3   -2  -1

# 2c) REMOVE_ITEM
list (REMOVE_ITEM VAR a 2.718)
message (${VAR}) 			# prints bdef1.6XX

# 2d) INSERT 
list (INSERT VAR 2 WW YY)
message (${VAR}) 			# prints bdWWYYef1.6XX

# 2e) REVERSE
list (REVERSE VAR)
message (${VAR}) 			# prints XX1.6feYYWWdb

# 2f) REMOVE_DUPLICATES
list (INSERT VAR 2 5)		# Adds 5 at position 2, VAR=XX1.65feYYWWdb
list (INSERT VAR 7 5)		# Adds 5 at position 7, VAR=XX1.65feYYWW5db
message (${VAR}) 			# prints XX1.65feYYWW5db

list (REMOVE_DUPLICATES VAR)# Removes 5 from position 7, because it is duplicate of 5 at position 2
message (${VAR}) 			# prints XX1.65feYYWWdb

# 2g) SORT
# VAR is currently XX 1.6 5 f e YY WW d b
list (SORT VAR)
message (${VAR})			# prints 1.65WWXXYYbdef

# ----------------- *** --------------------
# VAR is currently 1.6 5 WW XX YY b d e f
#                   0  1 2  3  4  5 6 7 8
# LENGTH,GET,SUBLIST,JOIN,FIND are commands that return value.

list (LENGTH VAR len_var)
message (${len_var})

list (GET VAR 2 5 7 sub_list)
message (${sub_list}) 		# prints  WWbe

list (SUBLIST VAR 2 3 sub_list2) 	# get 3 items from position [2,5)
message (${sub_list2}) 				# prints WWXXYY

list (JOIN VAR | str_var)
message (${str_var})				# prints 1.6|5|WW|XX|YY|b|d|e|f
list (JOIN VAR , str_var1)			
message (${str_var1})				# prints 1.6,5,WW,XX,YY,b,d,e,f

list (FIND VAR XX find_var) 
message (${find_var})				# prints 3
list (FIND VAR 1.6 find_var) 
message (${find_var})				# prints 0
list (FIND VAR f find_var) 
message (${find_var})				# prints 8
list (FIND VAR ZZ find_var) 
message (${find_var})				# prints -1, because ZZ is not found !

# --------------- *** --------------------------
# CMake string() commands
#
#	* FIND
#	* REPLACE
#	* PREPEND
#	* APPEND
#	* TOLOWER
#	* TOUPPER
#	* COMPARE
##-----------------------------------------------

set (VAR "CMake for Cross-Platform C++ Projects") 	# Set VAR to string

# FIND
string(FIND ${VAR} "For" find_var)					# returns -1 in find_var as "For" is not found
message (${find_var})								# prints -1

# REPLACE
message ("Before REPLACE : \'${VAR}\'") 
string (REPLACE "Projects" "Project" ret_var ${VAR})	# Replaces Projects with Project
message ("After  REPLACE : \'${ret_var}\'") 

# PREPEND
message ("Before PREPEND : \'${ret_var}\'") 
string (PREPEND ret_var "Master ")
message ("After  PREPEND : \'${ret_var}\'") 

# APPEND
message ("Before APPEND : \'${ret_var}\'") 
string (APPEND ret_var " Building")
message ("After  APPEND : \'${ret_var}\'") 

# TOLOWER
message ("Before TOLOWER : \'${ret_var}\'") 
string (TOLOWER ${ret_var} lower_case)
message ("After  TOLOWER : \'${lower_case}\'") 

# TOUPPER
message ("Before TOUPPER : \'${ret_var}\'") 
string (TOUPPER ${ret_var} upper_case)
message ("After  TOUPPER : \'${upper_case}\'") 

# COMPARE
string (COMPARE EQUAL ${upper_case} "MASTER CMAKE FOR CROSS-PLATFORM C++ PROJECT BUILDING" op_var)
message (${op_var})

#-----------------------------------------------
# file() -- operate on files !
# * READ
# * WRITE
# * RENAME
# * REMOVE
# * COPY
# * DOWNLOAD
# * LOCK
#-----------------------------------------------

# Quiz 1>
set (MY_LIST a;b c)
message ("MY LIST is ${MY_LIST}") 	# prints MY LIST is a;b;c

# Quiz 2>
set(LIST a;b;c)
message(${LIST})					# prints abc
