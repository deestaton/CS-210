import re
import string

# Path to txt file --> Change path to where you saved the file when testing
path = r"C:\Users\dopej\source\repos\CS210-Corner-Grocer\Release\items_list.txt"

# Empty dict stores items from file
items_list = {}

# Loop through each line in file and count number of times purchased then store in dict
f = open(path, "r")
lines = f.readlines()
#with open(path, "r") as f:
for data in lines:
	# If the item is already in the dict then increment by one
	if data.strip() in items_list:
		items_list[data.strip()] = items_list[data.strip()] + 1
	else:
		# Otherwise add item to the dict with count 1
		items_list[data.strip()] = 1 
f.close()

# Produces a list of all items and times purchased
def ViewAllItems():
	print("Purchase History")
	print("================\n")
	
	for key, value in list(items_list.items()):
		print("Item: {}, Purchased: {}x\n".format(key, value))


# Displays a single item and the number of times purchased
def ViewSingleItem(user_search):
	print("Item Search Result")
	print("===========\n")

	if user_search.strip() in items_list:
		print("Item: {}, Purchased: {}x".format(user_search.strip(), items_list[user_search.strip()]))
		return 0 
	print("Item: {} not found".format(user_search.strip()))
	return -1

# Displays a histogram 	
def ViewHistogram():
	new_f = open("frequency.dat", "w+")
	
	for k, v in list(items_list.items()):
		v = str(v).replace(str(v), v * "*")
		new_f.write(str(k) + " " + str(v) + "\n")
		print(str(k) + " " + str(v) + "\n")

	new_f.close()


#def printsomething():
#	print("Hello from Python!")
	

#def PrintMe(v):
#	print("You sent me: " + v)
#	return 100

#def SquareValue(v):
#	return v * v



