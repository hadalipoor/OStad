import os
import subprocess

def is_in_path(path_to_check, env_path):
    paths = env_path.split(os.pathsep)
    return path_to_check.lower() in (p.lower() for p in paths)

def add_to_user_path(path_to_add):
    try:
        subprocess.check_call(['setx', 'PATH', f"{os.environ['PATH']}{os.pathsep}{path_to_add}"])
        print(f"Added '{path_to_add}' to user's PATH.")
    except subprocess.CalledProcessError:
        print("Failed to add to user's PATH. Ensure you have the necessary permissions and setx is available.")

def main():
    arduino_cli_path = r"C:\Program Files\Arduino CLI"
    full_path = os.path.join(arduino_cli_path, "arduino-cli.exe")
    
    if not os.path.exists(full_path):
        print(f"The path '{full_path}' does not exist.")
        return

    if not is_in_path(arduino_cli_path, os.environ['PATH']):
        print("arduino-cli not found in PATH. Adding it...")
        add_to_user_path(arduino_cli_path)
    else:
        print("arduino-cli is already in PATH.")

if __name__ == "__main__":
    main()
