from subprocess import Popen, PIPE

class InteractiveProgram:
    def __init__(self, executable, display_messages=True):
        if executable[-3:] == '.py':
            executable = "python -u %s" % (executable, )

        self.process = Popen(executable, shell=True, stdin=PIPE, stdout=PIPE)

        self.display_messages = display_messages

    def send_line(self, s):
        if self.display_messages:
            print "Sending '%s' to process" % (s, )

        self.process.stdin.write(s + '\n')

        self.process.stdin.flush()

    def receive_line(self):
        s = self.process.stdout.readline().rstrip()

        if self.display_messages:
            print "Got '%s' from process" % (s, )

        return s

    def wait(self):
        exit_code = self.process.wait()

        if self.display_messages:
            print "Process exited with code %s" % (exit_code, )

        return exit_code
