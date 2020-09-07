# clean up and validate user input
def validate_matrix_m(m1, m2, operation):
    m1_clean = ""
    m2_clean = ""
    
    # removing whitespace
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


        # format user input (Ex. -n 1 2 3 -n 4 5 6 -n 7 8 9)
        if is_valid == 1:
            for i in m1_split:
                m1_clean += "-n "
                for j in i:

                    if "." not in j:
                        # filtering out non-numerical characters (unless it is a fraction)
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

                    # filtering out decimals (program only takes in integers and fractions)
                    else:
                        is_valid = 0
                        message = "Demical values are not valid. Please use integer and/or fraction (i.e. -3/5) values."
                        break


        if is_valid == 1:  
               for i in m2_split:
                    m2_clean += "-n "
                    for j in i:
                        if "." not in j:
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

                        else:
                            is_valid = 0
                            message = "Decimal values are not valid. Please use integer and/or fraction (i.e. -3/5) values."
                            break

    
    data = {
        'is_valid': str(is_valid),
        'm1': m1_clean,
        'm2': m2_clean,
        'operation': operation,
        'message': message,
    }

    return data

# formats user input (Ex. ./a.out -m 2 -m1 -n 1 2 3 -n 4 5 6 -m2 -n 1 2 3 -n 4 5 6)
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

# formats c++ output (answer)
def format_output_m(output):
    answer = ""

    for i in output:
        answer += str(i)[2:-3] + "-n "

    return answer

            
