use std::error::Error;
use std::fs::{self, File};
use std::io::{BufRead, BufReader};
use std::path::{Path, PathBuf};
use std::collections::HashMap;

fn main() -> Result<(), Box<dyn Error>> {
    let time = std::time::Instant::now();

    let files = get_files(".".as_ref())?;
    let file_data = analyze_files(&files)?;

    print_summary(&file_data)?;

    let elapsed = time.elapsed();
    println!("Process finished after {}ms", elapsed.as_millis());

    Ok(())
}

#[derive(Debug)]
struct FileData {
    lines: usize,
    characters: usize,
    files: usize,
}

fn analyze_files(files: &[PathBuf]) -> Result<HashMap<String, FileData>, Box<dyn Error>> {
    let mut file_data = HashMap::new();

    for file in files {
        if let Some(extension) = file.extension().and_then(|e| e.to_str()) {
            let entry = file_data.entry(extension.to_string()).or_insert(FileData {
                lines: 0,
                characters: 0,
                files: 0,
            });
            let file = File::open(file)?;
            let reader = BufReader::new(file);
            let (lines, characters) = count_lines_and_characters(reader)?;
            entry.lines += lines;
            entry.characters += characters;
            entry.files += 1;
        }
    }

    Ok(file_data)
}

fn get_files(dir: &Path) -> Result<Vec<PathBuf>, Box<dyn Error>> {
    let mut files = Vec::new();
    for entry in fs::read_dir(dir)? {
        let entry = entry?;
        let path = entry.path();
        if path.is_dir() {
            files.append(&mut get_files(&path)?);
        } else {
            files.push(path);
        }
    }
    Ok(files)
}

fn read_line(line: &str) -> (usize, usize) {
    let mut line_length = 0;
    let mut char_count = 0;
    for c in line.chars() {
        line_length += 1;
        if !c.is_whitespace() {
            char_count += 1;
        }
    }
    (1, char_count)
}

fn count_lines_and_characters<R: BufRead>(reader: R) -> Result<(usize, usize), Box<dyn Error>> {
    let (lines, characters) = reader.lines().fold((0, 0), |acc, line| {
        let (line_count, char_count) = read_line(&line?);
        (acc.0 + line_count, acc.1 + char_count)
    });
    Ok((lines, characters))
}

fn print_summary(file_data: &HashMap<String, FileData>) -> Result<(), Box<dyn Error>> {
    let mut sorted_data: Vec<_> = file_data.iter().collect();
    sorted_data.sort_by_key(|(_, data)| data.lines);

    for (extension, data) in sorted_data.iter() {
        println!(
            "{}:\n\t- {} Line(s)\n\t- {} Character(s)\n\t- {} File(s)",
            extension, data.lines, data.characters, data.files
        );
    }

    Ok(())
}