import os
import sys
import json
import argparse
import tkinter as tk
from tkinter import filedialog
sys.path.append(os.path.join(os.path.dirname(__file__), 'generator'))
from generator import *
import json

def validate_json_structure(json_string):
    try:
        # data = json.loads(json_string)
        data = json_string
        # Check for the presence of specific top-level keys
        required_top_level_keys = ["ProjectName", "ProjectPath", "Entities", "Apis", "Modules", "Configs"]
        if not all(key in data for key in required_top_level_keys):
            return False

        # Check Entities structure
        for entity in data["Entities"]:
            if "name" not in entity or "columns" not in entity:
                return False
            if not entity["columns"]:  # columns cannot be empty
                return False

        # Check Apis structure
        for api in data["Apis"]:
            if "name" not in api or "Url" not in api or "Apis" not in api:
                return False
            for sub_api in api["Apis"]:
                if "ApiName" not in sub_api or "EndPoint" not in sub_api or "Method" not in sub_api:
                    return False
                # "Data" can be empty, no need to check

        # Check Modules presence
        if "Modules" not in data:
            return False

        # Check Configs structure
        if "Configs" not in data:
            return False

        return True

    except json.JSONDecodeError:
        # Not a valid JSON
        return False

# You can test this function with various JSON strings in your environment

def generate_from_cli(path):
    with open(path, 'r') as f:
        json_data = json.load(f)
    if not validate_json_structure(json_data):
        return "wrong json format"
    return generate_all(json_data)

def generate_from_gui():
    def select_file():
        filename = filedialog.askopenfilename(filetypes=[("JSON files", "*.json")])
        if filename:
            file_path_entry.delete(0, tk.END)
            file_path_entry.insert(0, filename)

    def open_project_path(path):
        os.startfile(path)

    def generate_code():
        filename = file_path_entry.get()
        if filename:
            try:
                with open(filename, 'r') as f:
                    json_data = json.load(f)
                if not validate_json_structure(json_data):
                    result = {'message': "wrong json format",
                            'project_path' : '',
                            'project_name' : ''}
                else:
                    result = generate_all(json_data)
                    open_project_button.config(command=lambda: open_project_path(os.path.join(project_path, project_name)))
                    open_project_button.pack(pady=10)  # Show the button

                message = result['message']
                project_path = result['project_path']
                project_name = result['project_name']
                result_label.config(text=message)
            except Exception as e:
                result_label.config(text=f"Error: {e}")

    root = tk.Tk()
    root.title("OStad Code Generator")
    root.geometry("600x400")

    # Styling
    button_style = {'font': ('Arial', 12), 'fg': 'white', 'bg': 'blue', 'padx': 10, 'pady': 5}
    entry_style = {'font': ('Arial', 10), 'width': 50}
    label_style = {'font': ('Arial', 10), 'wraplength': 350}

    # File Path Entry
    file_path_entry = tk.Entry(root, **entry_style)
    file_path_entry.pack(pady=10)

    # Open File Button
    open_button = tk.Button(root, text="Open JSON File", command=select_file, **button_style)
    open_button.pack(pady=10)

    # Generate Code Button
    generate_button = tk.Button(root, text="Generate Code", command=generate_code, **button_style)
    generate_button.pack(pady=10)

    # Result Label
    result_label = tk.Label(root, text="", **label_style)
    result_label.pack(pady=20)

    # Open Project Path Button (Initially Hidden)
    open_project_button = tk.Button(root, text="Open Generated Project", **button_style)

    root.mainloop()


def main():
    parser = argparse.ArgumentParser(description="JSON File Generator")
    parser.add_argument("command", nargs='?', help="Command to execute ('generate')")
    parser.add_argument("JSON_PATH", nargs='?', help="Path to JSON file")
    args = parser.parse_args()

    if args.command == "generate" and args.JSON_PATH:
        message = generate_from_cli(args.JSON_PATH)
        print(message)
    else:
        generate_from_gui()

if __name__ == '__main__':
    main()
