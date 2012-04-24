class 'Test' (Script)

function Test:__init()
	Script.__init(self)
	
	self.axis = Vector3Attribute("axis", Vector3(1, 1, 0))
	self : addAttribute(self.axis)
	
	self.rotationSpeed = NumberAttribute("rotationSpeed", 1)
	self : addAttribute(self.rotationSpeed)
	
	self.rotationAmount = NumberAttribute("rotationAmount", 0)
	self : addAttribute(self.rotationAmount)
	
	self.transform = TransformDependency()
	self : addDependency(self.transform)
end

function Test:logicUpdate(timeStep)
	local axis = self.axis.value
	local angle = self.rotationSpeed.value * timeStep
	
	self.rotationAmount.value = self.rotationAmount.value + angle
	
	self.transform.component : rotate(axis, Radian(angle))
end
