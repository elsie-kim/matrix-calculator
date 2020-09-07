# cleans and validates user input
def validate_matrix_sm(m):
    m_clean = ""

    m_split = m.splitlines()
    m_split = [i for i in m_split if i != "" and i != " "]
    
    for x in range(len(m_split)):
        m_split[x] = m_split[x].split(" ")
        m_split[x] = [i for i in m_split[x] if i != "" and i != " "]
        
    is_valid = 2
    message = ""

    for i in range(len(m_split)-1):
        if len(m_split[i]) != len(m_split[i+1]):
            is_valid = 0
            message = "All rows must be equal in dimension"
            break

        else:
            is_valid = 1

    if is_valid == 1 and len(m_split) > len(m_split[0]):
        is_valid = 0
        message = "The number of rows cannot be greater than the number of columns"

    if is_valid == 1:
        for i in m_split:
            m_clean += "-n "

            for j in i:
                if "." not in j:
                    try:
                        j = int(j)
                        
                        m_clean += str(j) + " "

                    except:
                        if "/" in j:
                            index_slash = j.find("/")
                               
                            try:
                                m = int(j[0:index_slash])
                                n = int(j[index_slash+1:])

                                m_clean += str(m) + "/" + str(n) + " "

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
        'is_valid': is_valid,
        'm': m_clean,
        'message': message,
    }

    return data

# formats user input (Ex. ./a.out -m 3 -n 1 2 3 -n 4 5 6)
def format_input_sm(m):
    input_cmd = ['./a.out', '-m', "3"]
    
    for i in m.split(" "):
        if i != "":
            input_cmd.append(i)

    return input_cmd

# formats ouput from c++ file (answer)
def format_output_sm(output):
    answer = ""

    for i in output:
        answer += str(i)[2:-3] + "-n "

    return answer
