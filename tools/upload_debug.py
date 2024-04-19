import time
import requests
import socket
import os
import sys
import json
import shutil
from subprocess import check_output



def get_arduino_cli(dir_path):
    f = open(dir_path + '\\.vscode\\arduino.json')
    data = json.load(f)
    ino_file_basename = os.path.splitext(os.path.basename(data['sketch']))[0]
    try:
        socket.inet_aton(data['port'])
        compile_command = ['arduino-cli', 'compile', '--fqbn', data['board'], '--output-dir', dir_path + '\\.vscode\\.build', dir_path]
        # valid IP address
        # espota_path = "C:\\Users\\AIVWA 1\\AppData\\Local\\Arduino15\\packages\\esp32\\hardware\\esp32\\1.0.6\\tools\\espota.py"
        bin_path = os.path.join(dir_path, '.vscode', '.build', f'{ino_file_basename}.ino.bin')
        # upload_command = ['python', espota_path, '-d' , '-i', data['port'], '-f', bin_path]
        url = 'http://' + data['port'] + '/upload_sketch'
        upload_command = ['ip', url, bin_path]        
    except socket.error:
        compile_command = ['arduino-cli', 'compile', '--fqbn', data['board'] , dir_path + '\\.vscode\\.build']
        upload_command = ['arduino-cli', 'upload', '-p', data['port'], '--fqbn', data['board'], dir_path + '\\.vscode\\.build']
    f.close()
    return compile_command, upload_command

def build_and_upload(dir_path):
    compile_command, upload_command = (get_arduino_cli(dir_path))

    print(compile_command)
    try:
        print('Verifing ...')
        now = time.time()
        out = check_output(compile_command)
        verify_time = time.time()
        difference = int(verify_time - now)
        print('Verified Successfully at ' + str(difference) + ' seconds.')
        print(upload_command)
        if(upload_command[0] == 'ip'):
            try:
                # Open the file in binary mode
                with open(upload_command[2], 'rb') as file:
                    # Perform the POST request
                    response = requests.post(upload_command[1], files={'file': file})

                # Print the response
                print(response.text)
            except Exception as ex:
                print('Upload to IP failed.')
            return
        print('Uploading ...')
        out2 = check_output(upload_command)
        upload_time = time.time()
        difference = int(upload_time - verify_time)
        print('Uploaded To board at ' + str(difference) + ' seconds.')
    except Exception as ex:
        print('Compile Failed.' + str(ex))
    

def changed_code(dir_path, source_file_path, new_file_path, debug_mode = '-d'):
    source_file = open(source_file_path, 'r')
    if(source_file_path[-4:] == '.ino'):
        new_file = open(dir_path + '\\.vscode\\.build\\.build.ino', 'w')
    else:
        new_file = open(new_file_path, 'w')
    count = 0
    debug_line = False
    breakpoint_type = 'bp'
    arguments = []
    declared_debug_pause = False
    while True:
        count += 1
    
        # Get next line from file
        line = source_file.readline()
        if not line:
            break
        
        space_before_code = ''
        if(line.__contains__('//bp') or line.__contains__('//sv')):
            if(line.__contains__('//bps')):
                breakpoint_type = 'bps'
            elif(line.__contains__('//svs')):
                breakpoint_type = 'svs'
            elif(line.__contains__('//bp')):
                breakpoint_type = 'bp'
            elif(line.__contains__('//sv')):
                breakpoint_type = 'sv'
            
            debug_line = True
            last_braket = False
            var_break_end_pos = 0
            finish = False
            for i in range(len(line)-1):
                if (finish):
                    break
                if(line[i:i+2] == '//'):
                    for d in range(i):
                        space_before_code += ' '
                if(line[i:i+1] == '['):
                    for j in range(i+1, len(line) - 1, 1):
                        if(line[j:j+1] == ']'):
                            for t in range(j+1,len(line)-1,1):
                                if(line[t:t+1] == ']'):
                                    last_braket = False
                                    var_break_end_pos = t
                                    break
                                else:
                                    last_braket = True
                            else:
                                last_braket = True

                            if(not last_braket):
                                j = var_break_end_pos+1
                                continue
                            var_start_index = i + 1
                            var_end_brakket = j
                            for k in range(i+1, j, 1):
                                if(line[k:k+1] == ','):
                                    arguments.append(line[var_start_index:k])
                                    var_start_index = k+1
                                    k += 1
                            if(last_braket):
                                arguments.append(line[var_start_index:var_end_brakket])
                                
                                finish = True
                                break
            

            
        elif (debug_line and debug_mode == '-d'):
            print( 'Debug Mode' if debug_mode == '-d' else 'Build Mode' )
            
            print('----------------------------------------------------------------------------------------------------------------')
            print("File: {} ; Line{}: {}".format(source_file_path,count, line.strip()))
            if(breakpoint_type != 'bps' and breakpoint_type != 'svs'):
                new_file.write(space_before_code + '//debug genrated.')
                new_file.write(space_before_code +'Serial.println(\"'+line[:-1]+'\");\n')
                new_file.write(space_before_code +'Serial.println(\"Break Point at ' + source_file_path.replace('\\','\\\\') + ' ; Line : ' + str(count) + '\");\n')
                
            for argg in arguments:
                if(not argg.__contains__("\"")):
                    new_file.write(space_before_code +"Serial.print(")
                    new_file.write("\" | " + argg + " = \"); ")
                new_file.write('Serial.print(')
                new_file.write(argg+");\n")
            new_file.write(space_before_code +'Serial.println(\"\");\n')
            while_content = """_debug_pause = true;\nSerial.println(\"Press \\\"p\\\" key to pass ...\");while(_debug_pause){
 if (Serial.available() > 0) {
     String incomingString = Serial.readString();
     if (incomingString == "p\\n") {
         _debug_pause = false;
         Serial.println("passed");
     }
 }
}
"""

            if(breakpoint_type == 'bp' or breakpoint_type == 'bps' and not declared_debug_pause):
                new_file.write('bool ' + while_content)
                declared_debug_pause = True
            elif(breakpoint_type == 'bp' or breakpoint_type == 'bps' and declared_debug_pause):
                new_file.write(while_content)
            new_file.write(line)
            debug_line = False
            arguments = []
        else:
            new_file.write(line)

        
    
    source_file.close()
    new_file.close()


def change_file(dir_path, source_file_path, debug_mode = '-d'):
    new_file_path = dir_path + "\\.vscode\\.build" + source_file_path[len(dir_path):]
    new_file_folder = ''
    for i in range(len(new_file_path)-1,0,-1):
        if(new_file_path[i:i+1] == '\\'):
            new_file_folder = new_file_path[:i]
            if not os.path.exists(new_file_folder):
                os.makedirs(new_file_folder)
            break
    # print("new_file_directory = "+ new_file_folder)
    changed_code(dir_path, source_file_path, new_file_path, debug_mode)
    # file_obj.writelines(new_content)
    # file_obj.close()
    # print("file "+ new_file_path + " Created.")

def get_files(dir_path):
    res = []

    # Iterate directory
    for path in os.listdir(dir_path):
        # check if current path is a file
        if os.path.isfile(os.path.join(dir_path, path)):
            if(path[-4:] == ".ino" or path[-4:] == ".cpp" or path[-2:] == ".h"):
                res.append(dir_path + '\\' + path)
        else:
            if(path[0:1] != '.'):
                res.extend(get_files(dir_path + '\\' + path))
                # print(dir_path + '\\' + path)
    return res

def main():
    if(sys.argv.__len__() > 2):
        debug_mode = sys.argv[2]
    if(sys.argv.__len__() > 1):
        folder_path = sys.argv[1]
        if(folder_path == '-c'):
            folder_path = os.getcwd()
    else:
        folder_path = os.getcwd()
        debug_mode = '-b'
    
    print('Folder Path : ' + folder_path)
    print( 'Debug Mode' if debug_mode == '-d' else 'Build Mode' )

    files = get_files(folder_path)
    if(os.path.exists(folder_path +  "\\.vscode\\.build")):
        shutil.rmtree(folder_path +  "\\.vscode\\.build")
    index = 0
    for file_path in files:
        index += 1
        change_file(folder_path,file_path, debug_mode)
    build_and_upload(folder_path)


if __name__ == "__main__":
   main()
