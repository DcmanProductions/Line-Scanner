// LFInteractive LLC. - All Rights Reserved
using System.Text;

internal class Program
{
    private record FileData(int Lines, string Extension, long Characters, int Files);

    private static async Task Main()
    {
        var time = DateTime.Now;
        var files = Directory.GetFiles(Environment.CurrentDirectory, "*.*", SearchOption.AllDirectories);
        var fileData = await GetFileDataAsync(files);

        Console.ForegroundColor = ConsoleColor.Green;
        foreach (var data in fileData)
        {
            Console.WriteLine($"{data.Extension}:");
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine($"\t- {data.Lines:N0} Line(s)");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine($"\t- {data.Characters:N0} Character(s)");
            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.WriteLine($"\t- {data.Files:N0} File(s)");
            Console.ForegroundColor = ConsoleColor.Green;
        }
        Console.ResetColor();

        var span = DateTime.Now - time;
        Console.WriteLine($"Process finished after {span.TotalMilliseconds:N2}ms");
    }

    private static async Task<FileData[]> GetFileDataAsync(string[] files)
    {
        Console.ForegroundColor = ConsoleColor.Yellow;
        Console.WriteLine($"Calculating lines from {files.Length:N0} files");

        var fileData = new Dictionary<string, FileData>();
        var tasks = new List<Task>();

        foreach (var file in files)
        {
            tasks.Add(Task.Run(async () =>
            {
                var extension = Path.GetExtension(file).ToLower();

                if (!fileData.ContainsKey(extension))
                {
                    fileData[extension] = new FileData(0, extension, 0, 0);
                }

                var lines = 0L;
                var characters = 0L;

                using (var stream = new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.ReadWrite, 4096, true))
                using (var reader = new StreamReader(stream, Encoding.UTF8, true, 4096, true))
                {
                    while (!reader.EndOfStream)
                    {
                        var line = await reader.ReadLineAsync();
                        lines++;
                        characters += line.Length;
                    }
                }

                lock (fileData)
                {
                    fileData[extension] = fileData[extension] with
                    {
                        Lines = fileData[extension].Lines + (int)lines,
                        Characters = fileData[extension].Characters + characters,
                        Files = fileData[extension].Files + 1
                    };
                }
            }));
        }

        await Task.WhenAll(tasks);

        return fileData.Values.OrderByDescending(x => x.Lines).ToArray();
    }
}