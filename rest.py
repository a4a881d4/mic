import subprocess as sub
import web
import json
import string

urls = ( 	'/run', 'run',
					'/cmd/([0-9]+)', 'cmd' )
cmds=[]
class cmd:
	def POST(self,order):
		cmdstr = web.input()
		order=int(order)
		while len(cmds)<order+1:
			cmds.append({})
		for item in cmdstr:
			cmdstr[item]=cmdstr[item].strip()
		cmds[int(order)]=cmdstr
		ret=json.dumps(cmds)
		return json.dumps({'err_code':0,'message':ret})

class run:
	def _procs(self,changed):
		procs=[]
		self.cmds = []
		for cmd in cmds:
			if cmd!={}:
				newcmd={}
				for key in cmd:
					if key in changed:
						newcmd[key]=changed[key]
					else:
						newcmd[key]=cmd[key]
				self.cmds.append(newcmd)
		for cnt in range(0,len(self.cmds)):
			input=None
			if cnt>0:
				input=procs[cnt-1].proc.stdout
				if 'pipe' in self.cmds[cnt]:
					if self.cmds[cnt]['pipe']=='stderr':
						input=procs[cnt-1].proc.stderr
			procs.append(Command(self.cmds[cnt],stdin=input,stderr=sub.PIPE))
		return procs[-1].proc.communicate()
	
	def GET(self):
		print "incoming"
		changed=web.input()
		out,err = self._procs(changed)
		ret={ 'err_code':0,
					'err_msg':err,
					'out_msg':out
				}
		return json.dumps(ret)
		
class Command(object):
	def __init__(self, cmd, stdin=None, stderr=None):
		self.cmd = []
		for key in string.split(cmd['order'], ','):
			self.cmd.append(cmd[key])
		print self.cmd
		self.proc = sub.Popen(self.cmd,stdout=sub.PIPE,stdin=stdin,stderr=stderr)

app = web.application(urls, globals())
if __name__ == "__main__":
    app.run()