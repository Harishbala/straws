class datasume_core:
    lines = ''
    
    def analyze(self, file_name):
        self.process_file(file_name)
        for line in self.lines:
            print(line)

    def process_file(self, file_name):
        file = open(file_name, 'r')
        try:
            self.lines = file.readlines()
        except Exception as ex:
            print('Failure to read log files')
            self.lines = ''
        file.close()

def main():
    ds = datasume_core()
    ds.analyze('log.txt')

if __name__ == '__main__':
    main()
