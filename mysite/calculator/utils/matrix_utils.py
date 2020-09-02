def validate_matrix_m(m1, m2, operation):
    m1_clean = ""
    m2_clean = ""

    m1_split = m1.splitlines()
    m1_split = [i for i in m1_split if i != "" and i != " "]

    m2_split = m2.splitlines()
    m2_split = [i for i in m2_split if i != "" and i != " "]

    for x in range(len(m1_split)):
        m1_split[x] = m1_split[x].split(" ")
        m1_split[x] = [i for i in m1_split[x] if i != "" and i != " "]

    for x in range(len(m2_split)):
        m2_split[x] = m2_split[x].split(" ")
        m2_split[x] = [i for i in m2_split[x] if i != "" and i != " "]

    is_valid = 2
    message = ""

    for i in range(len(m1_split)-1):
        if len(m1_split[i]) != len(m1_split[i+1]):
            is_valid = 0
            message = "All rows must be equal in dimension"
            break
        
        else:
            is_valid = 1
   
    if is_valid == 1:
        for i in range(len(m2_split)-1):
            if len(m2_split[i]) != len(m2_split[i+1]):
                is_valid = 0
                message = "All rows of a matrix must be equal in dimension"
                break
            
            else:
                if operation == "0":
                    if len(m1_split[0]) != len(m2_split):
                        is_valid = 0
                        message = "The first matrix must have an equal number of columns as the number of rows of the second matrix"
                        break
                else:
                    if not (len(m1_split) == len(m2_split) and len(m1_split[0]) == len(m2_split[0])):
                        is_valid = 0
                        message = "The two matrices must be equal in dimensions"
                        break

                is_valid = 1


        if is_valid == 1:
            for i in m1_split:
                m1_clean += "-n "
                for j in i:
                    try:
                        j = int(j)

                        m1_clean += str(j) + " "

                    except:
                        if "/" in j:
                            index_slash = j.find("/")

                            try:
                                m = int(j[0:index_slash])
                                n = int(j[index_slash+1:])

                                m1_clean += str(m) + "/" + str(n) + " "

                                is_valid = 1

                            except:
                                is_valid = 0
                                message = "Invalid characters"
                                break
                        else:
                            is_valid = 0
                            message = "Invalid characters"
                            break

        if is_valid == 1:  
               for i in m2_split:
                    m2_clean += "-n "
                    for j in i:
                        try:
                            j = int(j)

                            m2_clean += str(j) + " "

                        except:
                            if "/" in j:
                                index_slash = j.find("/")

                                try:
                                    m = int(j[0:index_slash])
                                    n = int(j[index_slash+1:])

                                    m2_clean += str(m) + "/" + str(n) + " "

                                    is_valid = 1

                                except:
                                    is_valid = 0
                                    message = "Invalid characters"
                                    break
                            else:
                                is_valid = 0
                                message = "Invalid characters"
                                break


    data = {
        'is_valid': str(is_valid),
        'm1': m1_clean,
        'm2': m2_clean,
        'operation': operation,
        'message': message,
    }

    return data
                
#
#
#    # split lines into individual components
#    # and add "-n" to indicate a new line, so that main.cpp
#    # can process the string and split into 2D vectors
#    for i in range(len(m1_split)-1):
#        x = m1_split[i].split()
#        y = m1_split[i+1].split()
#        
#        q = m2_split[i].split()
#        r = m2_split[i].split()
#
#        a = [i.strip(" ") for i in x]
#        b = [i.strip(" ") for i in y]
#
#        # for matrix A of dimensions (m x n) and matrix B of dimensions (p x q),
#        # n must be equal to p in order for multiplication to be a valid
#        # operation
#        if operation == "0":
#            if (len(a) != len(b) or len(q) != len(r) or len(m2_split) != len(b)):            
#                is_valid = 0
#                message = "The number of columns of matrix 1 must match the number of rows of matrix 2"
#                break
#            else:
#                is_valid = 1
#
#        # check that each row is of equal length
#        elif not (len(a) == len(b) == len(q) == len(r)):
#            is_valid = 0
#            if not (len(m1_split) == len(m2_split)): 
#                message = "All rows must be equal in dimension, and all columns must be equal in dimension"
#            else:
#                message = "Rows must be equal in dimension"
#            break
#        
#        elif not (len(m1_split) == len(m2_split)): # something like that
#            is_valid = 0
#            message = "Matrices must be of equal dimensions"
#            break
#
#        else:
#            is_valid = 1
#    
#    if is_valid == 1: #need if statement?
#        for i in m1_split:
#            m1_clean += "-n "
#
#            for j in i.split(" "):
#                try:
#                    j = int(j)
#
#                    m1_clean += str(j) + " "
#            
#                except:
#                    if j != " " or j != "":
#                        is_valid = 0
#
#                        if "/" in j:
#                            index_slash = j.find("/")
#                        
#                            try:
#                                m = int(j[0:index_slash])
#                                n = int(j[index_slash+1:])
#                                
#                                m1_clean += str(m) + "/" + str(n) + " "
#
#                                is_valid = 1
#
#                            except: #break?
#                                message = "Invalid characters"   
#                        
#                        else:
#                            message = "Invalid characters"
#
#          
#        for i in m2_split:
#            m2_clean += "-n "
#
#            for j in i.split(" "):
#                try:
#                    j = int(j)
#
#                    m2_clean += str(j) + " "
#
#                except:
#                    if j != " " or j != "":
#                        is_valid = 0
#
#                        if "/" in j:
#                            index_slash = j.find("/")
#
#                            try:
#                                m = int(j[0:index_slash])
#                                n = int(j[index_slash+1:])
#                                
#                                m2_clean += str(m) + "/" + str(n) + " "
#
#                                is_valid = 1
#
#                            except:
#                                message = "Invalid characters"
#
#                        else:
#                            message = "Invalid characters"

def format_input_m(m1, m2, operation):
    input_cmd = ['./a.out', '-m', operation, '-m1']

    for i in m1.split(" "):
        if i != "":
            input_cmd.append(i)
    
    input_cmd.append("-m2")

    for i in m2.split(" "):
        if i != "":
            input_cmd.append(i)

    return input_cmd

def format_output_m(output):
    answer = ""

    for i in output:
        answer += str(i)[2:-3] + "-n "

    return answer

            
