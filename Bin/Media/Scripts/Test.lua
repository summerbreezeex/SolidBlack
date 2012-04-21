class 'Test' (Script)

function Test:__init()
	Script.__init(self)
	
	self.axis = Vector3Attribute("axis", Vector3(1, 1, 0))
	self : addAttribute(self.axis)
	
	self.rotationSpeed = NumberAttribute("rotationSpeed", 1)
	self : addAttribute(self.rotationSpeed)
	
	self.transform = TransformDependency()
	self : addDependency(self.transform)
end

function Test:logicUpdate(timeStep)
	if not self.transform.component then
		return
	end
	
	local axis = self.axis.value
	local angle = self.rotationSpeed.value * timeStep
	self.transform.component : rotate(axis, Radian(angle))
end
