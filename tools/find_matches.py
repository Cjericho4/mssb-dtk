import json
import sys

def find_matched_functions(report_path):
    try:
        with open(report_path, 'r') as f:
            data = json.load(f)
        
        units = data.get('units', [])
        for unit in units:
            unit_name = unit.get('name', 'unknown')
            functions = unit.get('functions', [])
            for func in functions:
                func_match = func.get('fuzzy_match_percent', 0)
                size = int(func.get('size', 0))
                if func_match == 100.0:
                    print(f"Unit: {unit_name}, Function: {func.get('name')}, Size: {size}")
            
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        find_matched_functions(sys.argv[1])
    else:
        print("Usage: python find_matches.py <report.json>")
