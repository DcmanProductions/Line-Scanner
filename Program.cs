// LFInteractive LLC. - All Rights Reserved
internal class Program
{
    record File(int lines, string extension, long characters, int files);

    private static void Main()
    {
        DateTime time = DateTime.Now;
        File[] lines = GetLines(Directory.GetFiles(Environment.CurrentDirectory, "*.*", SearchOption.AllDirectories));
        foreach (File line in lines)
        {
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine($"{line.extension}:");

            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine($"\t- {line.lines:N0} Line(s)");

            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine($"\t- {line.characters:N0} Character(s)");

            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.WriteLine($"\t- {line.files:N0} File(s)");
        }
        Console.ResetColor();
        TimeSpan span = new(DateTime.Now.Ticks - time.Ticks);
        Console.WriteLine($"Process finished after {span.TotalMilliseconds}ms");
    }

    private static File[] GetLines(string[] files)
    {
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.WriteLine($"Calculating lines from {files.Length:N0} files");
        List<File> lines = new();
        foreach (string file in files)
        {
            string text = "";
            using (FileStream fs = new(file, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
            {
                using StreamReader reader = new(fs);
                text = reader.ReadToEnd();
            }
            string extension = new FileInfo(file).Extension.ToLower();
            File? line = lines.FirstOrDefault(i => i.extension == extension, null);
            int numOfLines = text.Split("\n").Length;
            long characters = text.ToCharArray().LongLength;
            int numOfFiles = 1;
            if (line != null)
            {
                numOfLines += line.lines;
                characters += line.characters;
                numOfFiles += line.files;
                lines.Remove(line);
            }
            lines.Add(new(numOfLines, extension, characters, numOfFiles));
        }
        return lines.OrderByDescending(i => i.lines).ToArray();
    }
}