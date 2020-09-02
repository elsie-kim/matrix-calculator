def clean_vector(v):
    v_split_2 = ""

    # removing any white space that may be at the beginning
    start = 0
    is_valid = 1
    for i in v:

        if i == " ":
            start += 1
        
        else:
            break

    v = v[start:]

    if v == "": #required?
        is_valid = 0
         
            
    elif v[0] == '(' and v[-1] == ')':
        # remove parentheses
        v_split = v[1:-1]

        # remove spaces
        v_split = v_split.split(" ")

        # remove commas and any non-numerical charcters
        for i in v_split:
            x = i.split(',')

            for j in x:
                try:
                    #finding non-numerical characters
                    j = int(j)

                    # add to new string which holds the "cleaned" input
                    v_split_2 += str(j) + " "

                except:
                    if j != "":
                        if "/" in j:
                            index_slash = j.find("/")

                            try:
                                a = int(j[0:index_slash])
                                b = int(j[index_slash+1:])

                                v_split_2 += str(a) + "/" + str(b) + " "

                            except:
                                is_valid = 0
                                v_split_2 = ""
                                break
                
                        
    else:
        v_split_2 = ""

    return [is_valid, v_split_2]

        

# cleans up user input and determines if the user's input is useable
def validate_vector_v(v1, v2, operation):
    v1_clean = ""
    v2_clean = ""
    message = ""
    is_valid = 1

    v1_validate = clean_vector(v1)
    
    if v1_validate[0] == 1:
        v2_validate = clean_vector(v2)

        if v2_validate[0] == 1:
            v1_clean = v1_validate[1]
            v2_clean = v2_validate[1]

            format_msg = format_message_v(v1_clean, v2_clean, operation)

            message = format_msg[0]
            is_valid = format_msg[1]

    else:
        is_valid = 0
        message = "Invalid input"




#    # removing any white space at the beginning
#    start = 0
#    for i in v:
#        if i == " ":
#            start += 1
#        else:
#            break
#    
#    v = v[start:]
#    
#    # return empty list to indicate empty input
#    if v == "":
#        message = ""
#
#    elif v[0] == '(' and v[-1] == ')':
#        # remove parentheses
#        v_split = v[1:-1]
#       
#        # remove spaces
#        v_split = v_split.split(' ')
#        v_split_2 = "" 
#        
#        # remove commas and any non-numerical characters
#        for i in v_split:
#            x = i.split(',')
#        
#            for j in x:
#                try:
#                    # finding non-numerical characters
#                    j = int(j)
#    
#                    # add to new string which holds the "cleaned" input
#                    v_split_2 += str(j) + " "
#            
#                except:
#                    if j != "":
#                        if "/" in j:
#                            int index_slash = find("/")
#
#                            try:
#                                a = int(j[index_slash])
#                                b = int(j[index_slash+1:])
#
#                            except:
#                                message = "Invalid characters" # Cant include message, but need a way to implement messages, is_valid
#                        
#                        message = "Invalid characters"
#                   
#                    
#
#        # return list of components
#        return v_split_2 

    data = {
        'is_valid': str(is_valid),
        'operation': operation,
        'v1': v1_clean,
        'v2': v2_clean,
        'message': message,
    }

    return data

# formats input going into c++ files
def format_input_v(v1, v2, operation):
    input_cmd = ['./a.out', '-v', operation, '-v1']
    
    v1 = v1.split(" ")
    v2 = v2.split(" ")

    for i in v1:
        if i != "":
            input_cmd.append(i)

    input_cmd.append("-v2")

    for i in v2:
        if i != "":
            input_cmd.append(i)
    
    return input_cmd

# formats output from c++ files
def format_output_v(answer):
    # convert to string from binary
    answer = str(answer)
    
    # parse 
    answer = answer[2:-3]

    return answer

def format_message_v(v1_clean, v2_clean, operation):
    if v1_clean != "" and v2_clean != "" and len(v1_clean.split(" ")) == len(v2_clean.split(" ")):
        if operation == "1":
            if len(v1_clean.split(" ")) == 4:
                is_valid = 1
                message = ""
            
            else:
                is_valid = 0
                message = "The cross product is limited to 3D vectors"

        else:
            is_valid = 1
            message = ""

    else:
        is_valid = 0
        message = "Invalid input"


    return [message, is_valid]
